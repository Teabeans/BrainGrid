package edu.uwb.braingrid.workbenchdashboard;

import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.control.SingleSelectionModel;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.layout.BorderPane;
import edu.uwb.braingrid.workbenchdashboard.nledit.NLedit;
import edu.uwb.braingrid.workbenchdashboard.provis.ProVis;
import edu.uwb.braingrid.workbenchdashboard.setup.SimStarter;
import edu.uwb.braingrid.workbenchdashboard.welcome.Welcome;
import javafx.stage.Stage;

public class WorkbenchDisplay extends BorderPane {	

	private MenuBar menu_bar_;
	private Stage primaryStage_;
	private TabPane tp_ = new TabPane();
	
	public WorkbenchDisplay(Stage primary_stage) {
		primaryStage_ = primary_stage;
		setTop(generateMenuBar(primaryStage_));
		pushWeclomePage();
		setCenter(tp_);
	}

	public MenuBar getMenuBar() {
		return menu_bar_;
	}

	private MenuBar generateMenuBar(Stage primary_stage) {
		menu_bar_ = new MenuBar();
		menu_bar_.getMenus().add(generateMenuFile(primary_stage));
		return menu_bar_;
	}

	private Menu generateMenuFile(Stage primary_stage) {
		Menu file_menu = new Menu("_File");
		file_menu.getItems().add(generateMenuNew(primary_stage));
		return file_menu;
	}

	private Menu generateMenuNew(Stage primary_stage) {
		Menu new_menu = new Menu("_New");

		// Generate Items
		MenuItem gsle = new MenuItem("_Growth Simulation Layout Editor");

		// Define Functionality
		gsle.setOnAction(event -> {
			pushGSLEPane();
		});

		// Generate Items
		MenuItem simstarter = new MenuItem("_Simulation Starter");

		// Define Functionality
		simstarter.setOnAction(event -> {
			pushSimStarterPage();
		});

		// Generate Items
		MenuItem provis = new MenuItem("_ProVis");

		// Define Functionality
		provis.setOnAction(event -> {
			pushProVisStarterPage();
		});

		// Add
		new_menu.getItems().add(gsle);
		new_menu.getItems().add(simstarter);
		new_menu.getItems().add(provis);
		return new_menu;
	}

	void pushGSLEPane() {
		pushNewTab("NL Edit", new NLedit());
		//new WorkbenchTab("GSLE", new NLedit(), this);
	}

	void pushWeclomePage() {
		pushNewTab("Welcome!", new Welcome());
		//new WorkbenchTab("Welcome!", new Welcome(), this);
	}

	void pushSimStarterPage() {
		pushNewTab("SimStarter!", new SimStarter());
		//new WorkbenchTab("SimStarter!", new SimStarter(), this);
	}

	void pushProVisStarterPage() {
		pushNewTab("ProVis!", new ProVis());
		//new WorkbenchTab("ProVis!", new ProVis(), this);
	}
	
	private void pushNewTab(String name, WorkbenchApp wbapp) {
		Tab tab = new Tab();
		tab.setText(name);
		tab.setContent(wbapp.getDisplay());
		tp_.getTabs().add(tab);
		SingleSelectionModel<Tab> selectionModel = tp_.getSelectionModel();
		selectionModel.select(tab);
	}
}
