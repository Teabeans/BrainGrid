package edu.uwb.braingrid.provenance.workbenchprov;
/////////////////CLEANED
import org.apache.jena.rdf.model.Resource;
import edu.uwb.braingrid.provenance.ProvMgr;
import java.util.Date;

/**
 * This class provides provenance recording operations specific to the
 * BrainGridWorkbench. Operations of the workbench are recorded within an
 * existing RDF model, which is not maintained by this class. All functions
 * require that the manager of an existing record of workbench related
 * provenance be specified in order to decouple this class from the maintenance
 * and interaction of multiple models.
 *
 * @author Del Davis
 */
public class WorkbenchOperationRecorder {

    private static final String uploadLabel = "upload";
    private static final String copyLabel = "copy";
    private static final String workbenchSoftwareAgentURI = "workbench";

    /**
     * Creates a provenance record for an upload operation which was executed by
     * a software agent.
     *
     * @param provMgr - The manager for the provenance
     * @param sourceEntityURI - A unique identifier for the original entity that
     * was uploaded (the machine location is inferred to be whatever the local
     * name space is set to)
     * @param entityLabel - A label used to describe the entity uploaded
     * @param destinationEntityURI - A unique identifier for the entity that was
     * generated on the remote host by the upload operation (the name space is
     * derived from the remoteLocation specified).
     * @param remoteLocation - An identifier for the remote machine where the
     * source entity was uploaded to.
     * @param activityURI - An identifier for the activity of uploading the
     * entity from the local host to the remote host.
     * @param timeUploadStarted - The date and time when the upload began.
     * @param timeUploadEnded - The date and time when the upload completed.
     * @return - The resource in the provenance record associated with the
     * upload activity.
     */
    public static Resource uploadFile(ProvMgr provMgr, String sourceEntityURI,
            String destinationEntityURI, String entityLabel, String remoteLocation,
            String activityURI, Date timeUploadStarted,
            Date timeUploadEnded) {
        // set the remote namespace where the new entity was created
        provMgr.setNsPrefix(ProvMgr.REMOTE_NS_PREFIX, remoteLocation);
        // specify upload as an activity (origin of upload is local NS)
        Resource uploadActivity
                = provMgr.addActivity(activityURI, uploadLabel, false, false);
        // define the local entity that was uploaded
        Resource sourceEntity
                = provMgr.addEntity(sourceEntityURI, entityLabel, null, null, false);
        // specify time the upload activity started
        provMgr.startedAtTime(uploadActivity, timeUploadStarted);
        // specify time the upload activity ended
        provMgr.endedAtTime(uploadActivity, new Date());
        // add new file created by upload (this is a remote entity)
        Resource destinationEntity
                = provMgr.addEntity(destinationEntityURI, entityLabel, remoteLocation, null, false);
        // add workbench as an agent
        Resource workbenchAgent
                = provMgr.addSoftwareAgent(workbenchSoftwareAgentURI, null, false, false);
        // associate the upload activity with the workbench software
        provMgr.wasAssociatedWith(uploadActivity, workbenchAgent);
        // original script was used in the upload operation
        provMgr.used(uploadActivity, sourceEntity);
        // remote script file was generated by the upload operation
        provMgr.generated(uploadActivity, destinationEntity);
        // show that new script file wasDerivedFrom original script file
        provMgr.wasDerivedFrom(destinationEntity, sourceEntity);
        return uploadActivity;
    }

    /**
     * Creates a provenance record for a file copy operation which was executed
     * by a software agent.
     *
     * @param provMgr - The manager for the provenance
     * @param sourceEntityURI - A unique identifier for the original entity that
     * was copied
     * @param entityLabel - A label used to describe the entity copied
     * @param destinationEntityURI - A unique identifier for the entity that was
     * generated by the upload operation
     * @param activityURI - An identifier for the activity of copying the entity
     * one location to another on the same machine
     * @param timeCopyStarted - The date and time when the copy began.
     * @param timeCopyEnded - The date and time when the copy completed.
     * @return - The resource in the provenance record associated with the copy
     * activity.
     */
    public static Resource copyFile(ProvMgr provMgr, String sourceEntityURI,
            String destinationEntityURI, String entityLabel, String activityURI,
            Date timeCopyStarted, Date timeCopyEnded) {
        // specify copy as an activity
        Resource copyActivity
                = provMgr.addActivity(activityURI, copyLabel, false, false);
        // define the local entity that was copied
        Resource sourceEntity
                = provMgr.addEntity(sourceEntityURI, entityLabel, null, null, false);
        // specify time the copy activity started
        provMgr.startedAtTime(copyActivity, timeCopyStarted);
        // specify time the upload activity ended
        provMgr.endedAtTime(copyActivity, new Date());
        // add new file created by upload (this is a local entity)
        Resource destinationEntity = provMgr.addEntity(destinationEntityURI,
                entityLabel, null,null, false);
        // add workbench as an agent
        Resource workbenchAgent = provMgr.addSoftwareAgent(
                workbenchSoftwareAgentURI, null, false, false);
        // associate the copy activity with the workbench software
        provMgr.wasAssociatedWith(copyActivity, workbenchAgent);
        // original script was used in the copy operation
        provMgr.used(copyActivity, sourceEntity);
        // remote script file was generated by the upload operation
        provMgr.generated(destinationEntity, copyActivity);
        // show that new file wasDerivedFrom original file
        provMgr.wasDerivedFrom(destinationEntity, sourceEntity);
        return copyActivity;
    }
}