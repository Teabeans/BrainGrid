package edu.uwb.braingrid.workbenchdashboard.simstarter;

import java.util.logging.Logger;

import javax.swing.JFileChooser;

import edu.uwb.braingrid.workbench.WorkbenchManager;
import edu.uwb.braingrid.workbenchdashboard.WorkbenchApp;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.Tab;
import javafx.scene.control.TextArea;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

public class SimStarter extends WorkbenchApp {
	private static final Logger LOG = Logger.getLogger(SimStarter.class.getName());
	public SimStarter(Tab tab) {
		super(tab);
		LOG.info("new " + getClass().getName());
		// initMenu();
		ssas_ = new SimStarterAttributesSelector(this, workbenchMgr);
		sim_starter_tool_bar_ = new SimStarterToolBar(this);
		bp_.setTop(sim_starter_tool_bar_);
		disableProjectAttributeRelatedButtons();
		initCenter();
		super.setTitle("SimStarter");
	}

	@Override
	public boolean close() {
		// TODO Auto-generated method stub
		return true;
	}

	@Override
	public Node getDisplay() {
		return bp_;
	}

	public void newProject() {
		if (workbenchMgr.newProject()) {
			ssas_.resetUILabelText();
			progress_bar_.setVisible(false);
			current_proj_lbl_.setText(workbenchMgr.getProjectName());
			sim_starter_tool_bar_.disableProvidence(!workbenchMgr.isProvEnabled());
			ssas_.disableConfigure(false);
			ssas_.disableSpecifyScript(false);
			sim_starter_tool_bar_.disableSave(false);
			super.setTitle(workbenchMgr.getProjectName());
		}
		setMsg();
	}

	public void openProject() {
		int code = workbenchMgr.openProject();
		switch (code) {
		case JFileChooser.APPROVE_OPTION:
			updateProjectOverview();
			break;
		case JFileChooser.CANCEL_OPTION:
			break;
		case JFileChooser.ERROR_OPTION:
			break;
		case WorkbenchManager.EXCEPTION_OPTION:
		default:
			ssas_.resetUILabelText();
			break;
		}
	}

	public void saveProject() {
		workbenchMgr.saveProject();
		setMsg();
	}

	public void viewProvenance() {
		setMsg();
		workbenchMgr.viewProvenance();
	}

	public void manageParamsClasses() {
		if (workbenchMgr.configureParamsClasses()) {
			updateProjectOverview();
		}
		setMsg();
	}

	private void initCenter() {
		project_title_label_.setText("Current Project: ");
		current_proj_lbl_.setText("None");
		HBox proj = new HBox(project_title_label_, current_proj_lbl_);
		// VBox center = new VBox(proj, initAttributeDisplay(), msgText);
		VBox center = new VBox(proj, ssas_, msgText);
		bp_.setCenter(center);
	}

	public void updateProjectOverview() {
		ssas_.resetUILabelText();
		current_proj_lbl_.setText(workbenchMgr.getProjectName());
		// transferProgressBar.setVisible(workbenchMgr.isSimExecutionRemote());
		ssas_.updateProject();
		// enableInitialButtons();
	}

	public void disableProjectAttributeRelatedButtons() {
		ssas_.disableButtons();
		sim_starter_tool_bar_.disableSave(true);
	}

	/**
	 * Sets the workbench message content. The content of this message is based on
	 * the accumulated messages of produced by the functions of the workbench
	 * manager.
	 *
	 */
	public void setMsg() {
		msgText.setText(workbenchMgr.getMessages());
	}

	
	private BorderPane bp_ = new BorderPane();

	private Label project_title_label_ = new Label();
	private Label current_proj_lbl_ = new Label();
	private ProgressBar progress_bar_ = new ProgressBar(0);
	private TextArea msgText = new TextArea("");

	private WorkbenchManager workbenchMgr = new WorkbenchManager();
	private SimStarterToolBar sim_starter_tool_bar_;
	private SimStarterAttributesSelector ssas_;
}
