package edu.uwb.braingrid.workbench.ui;

import edu.uwb.braingrid.workbench.comm.SecureFileTransfer;
import edu.uwb.braingrid.workbench.model.SimulationSpecification;
import jdk.internal.jline.internal.Log;

import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Specifies the context for a simulation execution script. For example, should
 * the sequential version of the simulator be used to perform the simulation, or
 * should the parallel version be used? Will the source code be updated first?
 * Will the simulator be executed remotely? Answers to these questions determine
 * the content of the execution script to be generated; they also determine how
 * and where the script will be executed.
 *
 * @author Del Davis
 */
public class ScriptSpecificationDialog extends javax.swing.JDialog {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	// <editor-fold defaultstate="collapsed" desc="Auto-Generated Code">
	/**
	 * This method is called from within the constructor to initialize the form.
	 * WARNING: Do NOT modify this code. The content of this method is always
	 * regenerated by the Form Editor.
	 */
	@SuppressWarnings("unchecked")
	// <editor-fold defaultstate="collapsed" desc="Generated
	// Code">//GEN-BEGIN:initComponents
	private void initComponents() {

		codeRepositoryLocationLabel = new javax.swing.JLabel();
		codeRepositoryLocationTextField = new javax.swing.JTextField();
		okButton = new javax.swing.JButton();
		cancelButton = new javax.swing.JButton();
		simulatorLocationTextField = new javax.swing.JTextField();
		simulatorFolderLocationLabel = new javax.swing.JLabel();
		simulationTypeLabel = new javax.swing.JLabel();
		simulationTypeComboBox = new javax.swing.JComboBox();
		versionAnnotationLabel = new javax.swing.JLabel();
		versionAnnotationTextField = new javax.swing.JTextField();
		simulatorLocationComboBox = new javax.swing.JComboBox();
		sourceCodeUpdatingLabel = new javax.swing.JLabel();
		simulatorLocationLabel = new javax.swing.JLabel();
		sourceCodeUpdatingComboBox = new javax.swing.JComboBox();
		testConnectionButton = new javax.swing.JButton();
		remoteSpecMessageContentLabel = new javax.swing.JLabel();
		hostAddressLabel = new javax.swing.JLabel();
		usernameLabel = new javax.swing.JLabel();
		passwordLabel = new javax.swing.JLabel();
		hostAddressTextField = new javax.swing.JTextField();
		usernameTextField = new javax.swing.JTextField();
		jSeparator2 = new javax.swing.JSeparator();
		passwordField = new javax.swing.JPasswordField();
		messageContentLabel = new javax.swing.JLabel();
		SHA1CheckoutKeyTextField = new javax.swing.JTextField();
		SHA1CheckoutKeyLabel = new javax.swing.JLabel();
		buildOptionComboBox = new javax.swing.JComboBox();
		BuildOptionLabel = new javax.swing.JLabel();

		setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
		setTitle("Script Specification");

		codeRepositoryLocationLabel.setText("BrainGrid Code Repository:");
		codeRepositoryLocationLabel.setToolTipText(
				"<html>Repository to pull from.<br>This URI must go to a local folder,<br>or to a valid network address</html>");

		codeRepositoryLocationTextField.setText(getDefaultCodeLocation());
		codeRepositoryLocationTextField.setToolTipText(
				"<html>Repository to pull from.<br>This URI must go to a local folder,<br>or to a valid network address</html>");
		codeRepositoryLocationTextField.addKeyListener(new java.awt.event.KeyAdapter() {
			public void keyReleased(java.awt.event.KeyEvent evt) {
				codeRepositoryLocationTextFieldKeyReleased(evt);
			}
		});

		okButton.setText("OK");
		okButton.setEnabled(false);
		okButton.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				okButtonActionPerformed(evt);
			}
		});

		cancelButton.setText("Cancel");
		cancelButton.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				cancelButtonActionPerformed(evt);
			}
		});

		simulatorLocationTextField.addKeyListener(new java.awt.event.KeyAdapter() {
			public void keyReleased(java.awt.event.KeyEvent evt) {
				simulatorLocationTextFieldKeyReleased(evt);
			}
		});

		simulatorFolderLocationLabel.setText("* Simulator Folder Location:");
		simulatorFolderLocationLabel
				.setToolTipText("<html>The top folder for your local code-base<br>(not a repository address)</html>");

		simulationTypeLabel.setText("Simulator Execution Type: ");
		simulationTypeLabel.setToolTipText(
				"<html>If you wish to run growth, choose sequential<br>If you wish to run growth_gpu, choose parallel</html>");

		simulationTypeComboBox
				.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Sequential", "Parallel" }));

		versionAnnotationLabel.setText("Version Annotation:");
		versionAnnotationLabel.setToolTipText(
				"<html>A meaningful annotation to pair with<br>your source code version information<br>such as the repository branch</html>");

		versionAnnotationTextField.setToolTipText(
				"<html>A meaningful annotation to pair with<br>your source code version information<br>such as the repository branch</html>");
		versionAnnotationTextField.addKeyListener(new java.awt.event.KeyAdapter() {
			public void keyReleased(java.awt.event.KeyEvent evt) {
				versionAnnotationTextFieldKeyReleased(evt);
			}
		});

		simulatorLocationComboBox.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "Local", "Remote" }));
		simulatorLocationComboBox.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				simulatorLocationComboBoxActionPerformed(evt);
			}
		});

		sourceCodeUpdatingLabel.setText("Source Code Updating:");
		sourceCodeUpdatingLabel
				.setToolTipText("<html>Directions for updating source code<br>prior to running the simulation</html>");

		simulatorLocationLabel.setText("Simulator Location: ");
		simulatorLocationLabel
				.setToolTipText("<html>Will you run BrainGrid on a remote<br>machine or on this machine?</html>");

		sourceCodeUpdatingComboBox.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "None", "Pull" }));

		testConnectionButton.setText("Test Connection");
		testConnectionButton.setEnabled(false);
		testConnectionButton.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				testConnectionButtonActionPerformed(evt);
			}
		});

		remoteSpecMessageContentLabel.setText("<html><i>Message:</i><text></text></html>");
		remoteSpecMessageContentLabel.setVerticalAlignment(javax.swing.SwingConstants.TOP);

		hostAddressLabel.setText("* Host Address:");
		hostAddressLabel.setEnabled(false);

		usernameLabel.setText("Username:");
		usernameLabel.setEnabled(false);

		passwordLabel.setText("Password:");
		passwordLabel.setEnabled(false);

		hostAddressTextField.setEnabled(false);
		hostAddressTextField.addKeyListener(new java.awt.event.KeyAdapter() {
			public void keyReleased(java.awt.event.KeyEvent evt) {
				hostAddressTextFieldKeyReleased(evt);
			}
		});

		usernameTextField.setEnabled(false);
		usernameTextField.addKeyListener(new java.awt.event.KeyAdapter() {
			public void keyReleased(java.awt.event.KeyEvent evt) {
				usernameTextFieldKeyReleased(evt);
			}
		});

		passwordField.setEnabled(false);
		passwordField.addKeyListener(new java.awt.event.KeyAdapter() {
			public void keyReleased(java.awt.event.KeyEvent evt) {
				passwordFieldKeyReleased(evt);
			}
		});

		messageContentLabel.setText("<html><i>Message:</i><text></text></html>");
		messageContentLabel.setVerticalAlignment(javax.swing.SwingConstants.TOP);

		SHA1CheckoutKeyTextField.setToolTipText(
				"<html>A meaningful annotation to pair with<br>your source code version information<br>such as the repository branch</html>");

		SHA1CheckoutKeyLabel.setText("SHA1 Checkout Key (optional):");
		SHA1CheckoutKeyLabel.setToolTipText(
				"<html>A meaningful annotation to pair with<br>your source code version information<br>such as the repository branch</html>");

		buildOptionComboBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Build", "Pre-built" }));
		buildOptionComboBox.addItemListener(new java.awt.event.ItemListener() {
			public void itemStateChanged(java.awt.event.ItemEvent evt) {
				buildOptionComboBoxItemStateChanged(evt);
			}
		});

		BuildOptionLabel.setText("Build Option:");

		javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
		getContentPane().setLayout(layout);
		layout.setHorizontalGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
				.addGroup(layout.createSequentialGroup().addContainerGap()
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
								.addGroup(layout.createSequentialGroup().addComponent(messageContentLabel)
										.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(okButton)
										.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(cancelButton))
								.addComponent(jSeparator2, javax.swing.GroupLayout.Alignment.TRAILING)
								.addGroup(layout.createSequentialGroup().addComponent(simulatorLocationLabel)
										.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(simulatorLocationComboBox, javax.swing.GroupLayout.PREFERRED_SIZE,
												117, javax.swing.GroupLayout.PREFERRED_SIZE))
								.addGroup(layout.createSequentialGroup().addComponent(sourceCodeUpdatingLabel)
										.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(sourceCodeUpdatingComboBox,
												javax.swing.GroupLayout.PREFERRED_SIZE,
												javax.swing.GroupLayout.DEFAULT_SIZE,
												javax.swing.GroupLayout.PREFERRED_SIZE))
								.addGroup(layout.createSequentialGroup()
										.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
												.addComponent(hostAddressLabel)
												.addComponent(usernameLabel, javax.swing.GroupLayout.Alignment.LEADING)
												.addComponent(passwordLabel, javax.swing.GroupLayout.Alignment.LEADING))
										.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addGroup(layout
												.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
												.addComponent(hostAddressTextField,
														javax.swing.GroupLayout.DEFAULT_SIZE, 425, Short.MAX_VALUE)
												.addComponent(usernameTextField,
														javax.swing.GroupLayout.Alignment.LEADING)
												.addComponent(passwordField,
														javax.swing.GroupLayout.Alignment.LEADING)))
								.addComponent(simulatorLocationTextField)
								.addComponent(codeRepositoryLocationTextField, javax.swing.GroupLayout.DEFAULT_SIZE,
										506, Short.MAX_VALUE)
								.addGroup(javax.swing.GroupLayout.Alignment.TRAILING,
										layout.createSequentialGroup().addComponent(remoteSpecMessageContentLabel)
												.addGap(18, 18, 18).addComponent(testConnectionButton))
								.addComponent(
										simulatorFolderLocationLabel, javax.swing.GroupLayout.DEFAULT_SIZE,
										javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
								.addGroup(layout.createSequentialGroup().addGroup(layout
										.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
										.addComponent(versionAnnotationLabel, javax.swing.GroupLayout.Alignment.LEADING,
												javax.swing.GroupLayout.DEFAULT_SIZE, 247, Short.MAX_VALUE)
										.addComponent(versionAnnotationTextField,
												javax.swing.GroupLayout.Alignment.LEADING))
										.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 12,
												Short.MAX_VALUE)
										.addGroup(layout
												.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
												.addComponent(SHA1CheckoutKeyTextField,
														javax.swing.GroupLayout.DEFAULT_SIZE, 247, Short.MAX_VALUE)
												.addComponent(
														SHA1CheckoutKeyLabel, javax.swing.GroupLayout.DEFAULT_SIZE,
														javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
								.addGroup(layout.createSequentialGroup().addGroup(layout
										.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
										.addComponent(codeRepositoryLocationLabel,
												javax.swing.GroupLayout.Alignment.LEADING,
												javax.swing.GroupLayout.DEFAULT_SIZE,
												javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
										.addGroup(javax.swing.GroupLayout.Alignment.LEADING,
												layout.createSequentialGroup().addComponent(simulationTypeLabel)
														.addPreferredGap(
																javax.swing.LayoutStyle.ComponentPlacement.RELATED)
														.addComponent(simulationTypeComboBox,
																javax.swing.GroupLayout.PREFERRED_SIZE,
																javax.swing.GroupLayout.DEFAULT_SIZE,
																javax.swing.GroupLayout.PREFERRED_SIZE)))
										.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED,
												javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
										.addComponent(BuildOptionLabel)
										.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
										.addComponent(buildOptionComboBox, javax.swing.GroupLayout.PREFERRED_SIZE,
												javax.swing.GroupLayout.DEFAULT_SIZE,
												javax.swing.GroupLayout.PREFERRED_SIZE)))
						.addContainerGap()));
		layout.setVerticalGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
				.addGroup(layout.createSequentialGroup().addGap(12, 12, 12)
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
								.addComponent(simulatorLocationLabel)
								.addComponent(simulatorLocationComboBox, javax.swing.GroupLayout.PREFERRED_SIZE,
										javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
						.addGap(18, 18, 18)
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
								.addComponent(hostAddressLabel).addComponent(hostAddressTextField,
										javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE,
										javax.swing.GroupLayout.PREFERRED_SIZE))
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
								.addComponent(usernameLabel)
								.addComponent(usernameTextField, javax.swing.GroupLayout.PREFERRED_SIZE,
										javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
								.addComponent(passwordLabel)
								.addComponent(passwordField, javax.swing.GroupLayout.PREFERRED_SIZE,
										javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
								.addComponent(testConnectionButton).addComponent(remoteSpecMessageContentLabel,
										javax.swing.GroupLayout.PREFERRED_SIZE, 23,
										javax.swing.GroupLayout.PREFERRED_SIZE))
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
						.addComponent(jSeparator2, javax.swing.GroupLayout.PREFERRED_SIZE, 2,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
						.addComponent(simulatorFolderLocationLabel)
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
						.addComponent(simulatorLocationTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 28,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
								.addComponent(simulationTypeLabel)
								.addComponent(simulationTypeComboBox, javax.swing.GroupLayout.PREFERRED_SIZE,
										javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
								.addComponent(buildOptionComboBox, javax.swing.GroupLayout.PREFERRED_SIZE,
										javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
								.addComponent(BuildOptionLabel))
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
						.addComponent(codeRepositoryLocationLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 14,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
						.addComponent(codeRepositoryLocationTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 29,
								javax.swing.GroupLayout.PREFERRED_SIZE)
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
								.addComponent(versionAnnotationLabel).addComponent(SHA1CheckoutKeyLabel))
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
								.addComponent(versionAnnotationTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 28,
										javax.swing.GroupLayout.PREFERRED_SIZE)
								.addComponent(SHA1CheckoutKeyTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 28,
										javax.swing.GroupLayout.PREFERRED_SIZE))
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
								.addComponent(sourceCodeUpdatingLabel)
								.addComponent(sourceCodeUpdatingComboBox, javax.swing.GroupLayout.PREFERRED_SIZE,
										javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
						.addGap(18, 18, 18)
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
								.addGroup(layout.createSequentialGroup()
										.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
												.addComponent(cancelButton).addComponent(okButton))
										.addContainerGap())
								.addComponent(messageContentLabel))));

		pack();
	}// </editor-fold>//GEN-END:initComponents

	private void cancelButtonActionPerformed(java.awt.event.ActionEvent evt) {// GEN-FIRST:event_cancelButtonActionPerformed
		cancel();
	}// GEN-LAST:event_cancelButtonActionPerformed

	private void okButtonActionPerformed(java.awt.event.ActionEvent evt) {// GEN-FIRST:event_okButtonActionPerformed
		specifySimulator();
	}// GEN-LAST:event_okButtonActionPerformed

	private void testConnectionButtonActionPerformed(java.awt.event.ActionEvent evt) {// GEN-FIRST:event_testConnectionButtonActionPerformed
		testConnection();
	}// GEN-LAST:event_testConnectionButtonActionPerformed

	private void simulatorLocationComboBoxActionPerformed(java.awt.event.ActionEvent evt) {// GEN-FIRST:event_simulatorLocationComboBoxActionPerformed
		remoteOrLocalSet();
	}// GEN-LAST:event_simulatorLocationComboBoxActionPerformed

	private void hostAddressTextFieldKeyReleased(java.awt.event.KeyEvent evt) {// GEN-FIRST:event_hostAddressTextFieldKeyReleased
		validateHostAddress();
		if (testConnectionButton.isEnabled()) {
			if (evt.getKeyCode() == KeyEvent.VK_ENTER) {
				testConnection();
			}
		}
	}// GEN-LAST:event_hostAddressTextFieldKeyReleased

	private void usernameTextFieldKeyReleased(java.awt.event.KeyEvent evt) {// GEN-FIRST:event_usernameTextFieldKeyReleased
		validateUsername();
		if (testConnectionButton.isEnabled()) {
			if (evt.getKeyCode() == KeyEvent.VK_ENTER) {
				testConnection();
			}
		}
	}// GEN-LAST:event_usernameTextFieldKeyReleased

	private void passwordFieldKeyReleased(java.awt.event.KeyEvent evt) {// GEN-FIRST:event_passwordFieldKeyReleased
		if (testConnectionButton.isEnabled()) {
			if (evt.getKeyCode() == KeyEvent.VK_ENTER) {
				testConnection();
			}
		}
	}// GEN-LAST:event_passwordFieldKeyReleased

	private void simulatorLocationTextFieldKeyReleased(java.awt.event.KeyEvent evt) {// GEN-FIRST:event_simulatorLocationTextFieldKeyReleased
		simulatorLocationChanged();
		if (okButton.isEnabled()) {
			if (evt.getKeyCode() == KeyEvent.VK_ENTER) {
				specifySimulator();
			}
		}
	}// GEN-LAST:event_simulatorLocationTextFieldKeyReleased

	private void codeRepositoryLocationTextFieldKeyReleased(java.awt.event.KeyEvent evt) {// GEN-FIRST:event_codeRepositoryLocationTextFieldKeyReleased
		if (okButton.isEnabled()) {
			if (evt.getKeyCode() == KeyEvent.VK_ENTER) {
				specifySimulator();
			}
		}
	}// GEN-LAST:event_codeRepositoryLocationTextFieldKeyReleased

	private void versionAnnotationTextFieldKeyReleased(java.awt.event.KeyEvent evt) {// GEN-FIRST:event_versionAnnotationTextFieldKeyReleased
		if (okButton.isEnabled()) {
			if (evt.getKeyCode() == KeyEvent.VK_ENTER) {
				specifySimulator();
			}
		}
	}// GEN-LAST:event_versionAnnotationTextFieldKeyReleased

	private void buildOptionComboBoxItemStateChanged(java.awt.event.ItemEvent evt) {// GEN-FIRST:event_buildOptionComboBoxItemStateChanged
		updateStateOnBuildOptionChange();
	}// GEN-LAST:event_buildOptionComboBoxItemStateChanged

	// Variables declaration - do not modify//GEN-BEGIN:variables
	private javax.swing.JLabel BuildOptionLabel;
	private javax.swing.JLabel SHA1CheckoutKeyLabel;
	private javax.swing.JTextField SHA1CheckoutKeyTextField;
	private javax.swing.JComboBox buildOptionComboBox;
	private javax.swing.JButton cancelButton;
	private javax.swing.JLabel codeRepositoryLocationLabel;
	private javax.swing.JTextField codeRepositoryLocationTextField;
	private javax.swing.JLabel hostAddressLabel;
	private javax.swing.JTextField hostAddressTextField;
	private javax.swing.JSeparator jSeparator2;
	private javax.swing.JLabel messageContentLabel;
	private javax.swing.JButton okButton;
	private javax.swing.JPasswordField passwordField;
	private javax.swing.JLabel passwordLabel;
	private javax.swing.JLabel remoteSpecMessageContentLabel;
	private javax.swing.JComboBox simulationTypeComboBox;
	private javax.swing.JLabel simulationTypeLabel;
	private javax.swing.JLabel simulatorFolderLocationLabel;
	private javax.swing.JComboBox simulatorLocationComboBox;
	private javax.swing.JLabel simulatorLocationLabel;
	private javax.swing.JTextField simulatorLocationTextField;
	private javax.swing.JComboBox sourceCodeUpdatingComboBox;
	private javax.swing.JLabel sourceCodeUpdatingLabel;
	private javax.swing.JButton testConnectionButton;
	private javax.swing.JLabel usernameLabel;
	private javax.swing.JTextField usernameTextField;
	private javax.swing.JLabel versionAnnotationLabel;
	private javax.swing.JTextField versionAnnotationTextField;
	// End of variables declaration//GEN-END:variables
	// </editor-fold>

	// <editor-fold defaultstate="collapsed" desc="Custom Members">
	/* Custom Members */
	public static final String LINUX_USERNAME_PATTERN = "^[a-z][a-z0-9\\-]*$";
	private String DEFAULT_REPO_URI = "https://github.com/UWB-Biocomputing/BrainGrid.git";
	private boolean okButtonClicked = false;
	private boolean connectionTestSuccessful = false;
	// </editor-fold>

	// <editor-fold defaultstate="collapsed" desc="Construction">
	/**
	 * Responsible for allocating a new dialog, instantiating and initializing all
	 * members, and making the dialog visible
	 *
	 * @param modal
	 *            - True if this dialog should prevent focus from shifting to it's
	 *            parent, False if the focus can shift to the parent while this
	 *            dialog is visible
	 */
	public ScriptSpecificationDialog(boolean modal) {
		Log.info("New ScriptSpecificationDialog");
		setModal(modal);
		initComponents();
		simulatorLocationTextField.setText("BrainGrid");
		center();
		pack();
		setVisible(true);
	}

	private String getDefaultCodeLocation() {
		return DEFAULT_REPO_URI;
	}

	public ScriptSpecificationDialog(boolean modal, SimulationSpecification simSpec) {
		Log.info("New ScriptSpecificationDialog with SimulationSpecification");
		setModal(modal);
		initComponents();

		boolean remote = simSpec.isRemote();
		String simType = simSpec.getSimulationType();
		String gitPull = simSpec.getSourceCodeUpdating();

		String hostAddr = simSpec.getHostAddr();
		String userName = simSpec.getUsername();
		String folder = simSpec.getSimulatorFolder();
		String codeLocation = simSpec.getCodeLocation();
		String SHA1Key = simSpec.hasCommitCheckout() ? simSpec.getSHA1CheckoutKey() : "";
		String buildOption = simSpec.getBuildOption();
		codeLocation = codeLocation == null || codeLocation.isEmpty() ? getDefaultCodeLocation() : codeLocation;
		String version = simSpec.getVersionAnnotation();

		if (remote) {
			simulatorLocationComboBox.setSelectedIndex(SimulationSpecification.REMOTE_EXECUTION_INDEX);
			if (hostAddr != null) {
				hostAddressTextField.setText(hostAddr);
			}
			if (userName != null) {
				usernameTextField.setText(userName);
			}
		} else {
			simulatorLocationComboBox.setSelectedIndex(SimulationSpecification.LOCAL_EXECUTION_INDEX);
		}

		if (simType != null) {
			if (simType.equals(SimulationSpecification.SEQUENTIAL_SIMULATION)) {
				simulatorLocationComboBox.setSelectedItem(SimulationSpecification.PARALLEL_SIMULATION_INDEX);
			} else {
				simulatorLocationComboBox.setSelectedItem(SimulationSpecification.SEQUENTIAL_SIMULATION_INDEX);
			}
		}

		if (buildOption != null) {
			if (buildOption.equals(SimulationSpecification.BUILD_BUILD_OPTION)) {
				buildOptionComboBox.setSelectedItem(SimulationSpecification.BUILD_BUILD_OPTION);
			} else {
				buildOptionComboBox.setSelectedItem(SimulationSpecification.PRE_BUILT_BUILD_OPTION);
			}
		}

		if (gitPull != null) {
			if (gitPull.equals(SimulationSpecification.GIT_PULL_AND_CLONE)) {
				sourceCodeUpdatingComboBox.setSelectedIndex(SimulationSpecification.GIT_PULL_AND_CLONE_INDEX);
			} else {
				sourceCodeUpdatingComboBox.setSelectedIndex(SimulationSpecification.GIT_NONE_INDEX);
			}
		}
		simulatorLocationTextField.setText(folder);
		codeRepositoryLocationTextField.setText(codeLocation);
		versionAnnotationTextField.setText(version);
		SHA1CheckoutKeyTextField.setText(SHA1Key);

		updateStateOnBuildOptionChange();
		enableOkButton();

		center();
		pack();
		setVisible(true);
	}

	private void center() {
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		Dimension frameSize = getSize();
		if (frameSize.height > screenSize.height) {
			frameSize.height = screenSize.height;
		}
		if (frameSize.width > screenSize.width) {
			frameSize.width = screenSize.width;
		}
		setLocation((screenSize.width - frameSize.width) / 2, (screenSize.height - frameSize.height) / 2);
	}
	// </editor-fold>

	// <editor-fold defaultstate="collapsed" desc="Action Helpers">
	private void specifySimulator() {
		String simFilePath = simulatorLocationTextField.getText();
		if (simFilePath.endsWith("/") || simFilePath.endsWith("\\")) {
			simFilePath = simFilePath.substring(0, simFilePath.length() - 1);
			simulatorLocationTextField.setText(simFilePath);
		}

		okButtonClicked = true;
		passwordField.setText(null);
		setVisible(false);
	}

	private void cancel() {
		okButtonClicked = false;
		setVisible(false);
	}

	private void remoteOrLocalSet() {
		setRemoteRelatedComponentsEnabled(
				simulatorLocationComboBox.getSelectedIndex() == SimulationSpecification.REMOTE_EXECUTION_INDEX);
	}

	private void validateHostAddress() {
		enableTestConnectionButton();
		if (hostAddressTextField.getText().equals("")) {
			setRemoteConnectionMsg("Invalid Host Address", "red");
		} else {
			setRemoteConnectionMsg("", "black");
		}
	}

	private void validateUsername() {
		enableTestConnectionButton();
		if (!isValidUsername(usernameTextField.getText())) {
			setRemoteConnectionMsg("Invalid Username", "red");
		} else {
			setRemoteConnectionMsg("", "black");
		}
	}

	private void testConnection() {
		testConnectionButton.setEnabled(false);
		String hostname = hostAddressTextField.getText();
		String username = usernameTextField.getText();
		char[] password = passwordField.getPassword();
		// try to connect
		SecureFileTransfer sft = new SecureFileTransfer();
		boolean success = sft.testConnection(3000, hostname, username, password);
		String msg = success ? "Connection Successful" : "Connection Failed";
		String color = success ? "green" : "red";
		// report status
		setRemoteConnectionMsg(msg, color);
		// mark operation success
		connectionTestSuccessful = success;
		Arrays.fill(password, '0');
		// reset button
		testConnectionButton.setEnabled(true);
	}

	private void simulatorLocationChanged() {
		enableOkButton();
	}

	// private boolean validateSimulatorLocation() {
	// return isValidFilename(simulatorLocationTextField.getText());
	// }
	//
	// private void validateCodeRepositoryLocation() {
	// }
	// </editor-fold>

	// <editor-fold defaultstate="collapsed" desc="Getters">
	/**
	 * Indicates the exit route taken by the user from this dialog.
	 *
	 * @return True if the user clicked OK, otherwise false.
	 */
	public boolean getSuccess() {
		return okButtonClicked;
	}

	/**
	 * Provides the location of the folder where the simulator will be
	 * (conditionally based on options set in the specification) cloned/checked out
	 * to, built, and executed.
	 *
	 * @return The location of the folder where the simulator will be (conditionally
	 *         based on options set in the specification) cloned/checked out to,
	 *         built, and executed.
	 */
	public String getSimulatorFolder() {
		return simulatorLocationTextField.getText();
	}

	/**
	 * Provides the location of the source code. If source code updating is turned
	 * off in this specification, then this location points to a folder on the
	 * machine where the simulation will take place. If source code updating is
	 * turned on in this specification, then this location points to a source code
	 * repository.
	 *
	 * @return The location of the source code
	 */
	public String getCodeLocation() {
		return codeRepositoryLocationTextField.getText();
	}

	/**
	 * Provides the annotation (a note) text entered by the user to describe the
	 * version of the simulator that will be executed
	 *
	 * @return The annotation (a note) text entered by the user to describe the
	 *         version of the simulator that will be executed
	 */
	public String getVersionAnnotation() {
		return versionAnnotationTextField.getText();
	}

	/**
	 * Provides the selected option text indicating the locale relationship between
	 * where the simulator will run and the local machine
	 *
	 * @return The selected option text indicating the locale relationship between
	 *         where the simulator will run and the local machine
	 */
	public String getSimulatorExecutionMachine() {
		return simulatorLocationComboBox.getSelectedItem().toString();
	}

	/**
	 * Provides the selected option text indicating which processor threading/core
	 * model should be used for a simulation
	 *
	 * @return The selected option text indicating which processor threading/core
	 *         model should be used for a simulation
	 */
	public String getSimulationType() {
		return simulationTypeComboBox.getSelectedItem().toString();
	}

	/**
	 * Provides the selected option text indicating whether source code should be
	 * updated prior to executing the simulation
	 *
	 * @return The option selected indicating whether source code should be updated
	 *         prior to executing the simulation
	 */
	public String getSourceCodeUpdating() {
		return sourceCodeUpdatingComboBox.getSelectedItem().toString();
	}

	/**
	 * Provides the host name or address entered or an empty string if the for the
	 * respective field is null
	 *
	 * @return The host name or address entered or an empty string if the for the
	 *         respective field is null
	 */
	public String getHostAddr() {
		return hostAddressTextField.getText() == null ? "" : hostAddressTextField.getText();
	}

	/**
	 * Provides the username entered or an empty string if the data for the field is
	 * null
	 *
	 * @return The username entered or an empty string if the data for the
	 *         respective field is null
	 */
	public String getUsername() {
		return usernameTextField.getText() == null ? "" : usernameTextField.getText();
	}

	/**
	 * Indicates whether or not testing the connection to the specified host, with
	 * the login credentials provided, was successful
	 *
	 * @return True if the connection test was successful, otherwise false
	 */
	public boolean testConnectionPassed() {
		return connectionTestSuccessful;
	}

	/**
	 * Provides a simulator specification with values set to their respective
	 * equivalents from this dialog
	 *
	 * @return A simulation specification populated from the state of this dialog
	 */
	public SimulationSpecification toSimulatorSpecification() {
		SimulationSpecification simSpec = new SimulationSpecification();
		simSpec.setSimulatorFolder(simulatorLocationTextField.getText());
		simSpec.setCodeLocation(codeRepositoryLocationTextField.getText());
		simSpec.setVersionAnnotation(versionAnnotationTextField.getText());
		String locale = simulatorLocationComboBox.getSelectedItem().toString();
		simSpec.setSimulatorLocale(locale);
		String type = simulationTypeComboBox.getSelectedItem().toString();
		simSpec.setSimulationType(type);
		String update = sourceCodeUpdatingComboBox.getSelectedItem().toString();
		simSpec.setSourceCodeUpdating(update);
		String address = hostAddressTextField.getText() == null ? "" : hostAddressTextField.getText();
		simSpec.setHostAddr(address);
		String username = usernameTextField.getText() == null ? "" : usernameTextField.getText();
		simSpec.setUsername(username);
		String sha1 = SHA1CheckoutKeyTextField.getText() == null ? "" : SHA1CheckoutKeyTextField.getText();
		simSpec.setSHA1CheckoutKey(sha1);
		String buildOption = buildOptionComboBox.getSelectedItem().toString();
		simSpec.setBuildOption(buildOption);

		return simSpec;
	}// </editor-fold>

	// <editor-fold defaultstate="collapsed" desc="UI Manipulation">
	private void setRemoteRelatedComponentsEnabled(boolean enabled) {
		hostAddressLabel.setEnabled(enabled);
		usernameLabel.setEnabled(enabled);
		passwordLabel.setEnabled(enabled);
		hostAddressTextField.setEnabled(enabled);
		usernameTextField.setEnabled(enabled);
		passwordField.setEnabled(enabled);
	}

	private void enableTestConnectionButton() {
		testConnectionButton.setEnabled(hostAddressTextField.getText() != null
				&& !hostAddressTextField.getText().equals("") && usernameTextField.getText() != null
				&& !usernameTextField.getText().equals("") && passwordField.getPassword() != null);
		connectionTestSuccessful = false;
	}
	// </editor-fold>

	// <editor-fold defaultstate="collapsed" desc="User Communication">
	private void setRemoteConnectionMsg(String msg, String color) {
		remoteSpecMessageContentLabel
				.setText("<html><i>Message: </i><b>" + "<span style=\"color:" + color + "\">" + msg + "</span></html>");
	}

//	private void setPathValidationMsg(String msg, String color) {
//		messageContentLabel
//				.setText("<html><i>Message: </i><b>" + "<span style=\"color:" + color + "\">" + msg + "</span></html>");
//	}
	// </editor-fold>

	// <editor-fold defaultstate="collapsed" desc="Validation">
	private boolean isValidUsername(String text) {
		return text.matches(LINUX_USERNAME_PATTERN);
	}

	/**
	 * Checks a string representing a filename for adherence to Windows filename
	 * conventions. Windows need not be the platform that this function is concerned
	 * with, it just happens to have the most restrictions on filename characters
	 *
	 * @param fileName
	 *            - string representing a filename
	 * @return True if the filename specified was valid, False if not
	 */
//	private static boolean isValidFilename(String fileName) {
//		Pattern pattern = Pattern.compile(
//				"# Match a valid Windows filename (unspecified file system).          \n"
//						+ "^                                # Anchor to start of string.        \n"
//						+ "(?!                              # Assert filename is not: CON, PRN, \n"
//						+ "  (?:                            # AUX, NUL, COM1, COM2, COM3, COM4, \n"
//						+ "    CON|PRN|AUX|NUL|             # COM5, COM6, COM7, COM8, COM9,     \n"
//						+ "    COM[1-9]|LPT[1-9]            # LPT1, LPT2, LPT3, LPT4, LPT5,     \n"
//						+ "  )                              # LPT6, LPT7, LPT8, and LPT9...     \n"
//						+ "  (?:\\.[^.]*)?                  # followed by optional extension    \n"
//						+ "  $                              # and end of string                 \n"
//						+ ")                                # End negative lookahead assertion. \n"
//						+ "[^<>:\"/\\\\|?*\\x00-\\x1F]*     # Zero or more valid filename chars.\n"
//						+ "[^<>:\"/\\\\|?*\\x00-\\x1F\\ .]  # Last char is not a space or dot.  \n"
//						+ "$                                # Anchor to end of string.            ",
//				Pattern.CASE_INSENSITIVE | Pattern.UNICODE_CASE | Pattern.COMMENTS);
//		Matcher matcher = pattern.matcher(fileName);
//		boolean isMatch = matcher.matches();
//		return isMatch;
//	}

	private void enableOkButton() {
		// determine if any requirements are null or empty
		boolean nullLocation = simulatorLocationTextField.getText() == null;
		boolean simulatorLocationEmpty = simulatorLocationTextField.getText().equals("");
		boolean remoteExecution = this.simulatorLocationComboBox.getSelectedItem().toString()
				.equals(SimulationSpecification.REMOTE_EXECUTION);
		boolean nullHostAddr = hostAddressTextField.getText() == null;
		boolean emptyHostAddr = hostAddressTextField.getText().equals("");
		// set ok enabled based on required fields filled
		if (remoteExecution) {
			okButton.setEnabled(!nullLocation && !simulatorLocationEmpty && !nullHostAddr && !emptyHostAddr);
		} else {
			okButton.setEnabled(!nullLocation && !simulatorLocationEmpty);
		}
	}
	// </editor-fold>

	private void updateStateOnBuildOptionChange() {
		String buildOption = buildOptionComboBox.getSelectedItem().toString();
		if (buildOption.equals(SimulationSpecification.PRE_BUILT_BUILD_OPTION)) {
			sourceCodeUpdatingComboBox.setSelectedItem(SimulationSpecification.GIT_NONE);
			sourceCodeUpdatingComboBox.setEnabled(false);
		} else {
			sourceCodeUpdatingComboBox.setEnabled(true);
			
		}
	}
}
