package edu.uwb.braingrid.workbenchdashboard.provis;

import java.util.logging.Logger;

import org.controlsfx.control.ToggleSwitch;

import edu.uwb.braingrid.workbench.provvisualizer.view.VisCanvas;
import edu.uwb.braingrid.workbenchdashboard.WorkbenchApp;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;
import javafx.scene.control.Tab;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;

public class ProVis extends WorkbenchApp {
	private static final Logger LOG = Logger.getLogger(ProVis.class.getName());

	public ProVis(Tab tab) {
		super(tab);
		LOG.info("new " + getClass().getName());
		adjust_force_slider_.setBlockIncrement(20);
		adjust_force_slider_.setMajorTickUnit(20);
		//adjust_force_slider_.setMinorTickCount(1);
		adjust_force_slider_.setShowTickLabels(true);
		adjust_force_slider_.setShowTickMarks(true);
		adjust_force_slider_.setSnapToTicks(true);

		stop_forces_.setMnemonicParsing(false);
		show_node_ids_.setMnemonicParsing(false);
		show_relationships_.setMnemonicParsing(false);
		show_legend_.setMnemonicParsing(false);

		pro_vis_ctrl_ = new ProVisCtrl(this, vis_canvas_, canvas_pane_, adjust_force_slider_, stop_forces_,
				show_node_ids_, show_relationships_, show_legend_, choose_file_btn_);

		canvas_pane_.getChildren().add(vis_canvas_);

		VBox vb = new VBox(stop_forces_, show_node_ids_, show_relationships_, show_legend_, adjust_force_slider_,
				choose_file_btn_);
		vb.getStyleClass().add("controls");
		bp_.setCenter(canvas_pane_);
		bp_.setRight(vb);

		super.setTitle("ProVis");
	}

	@Override
	public boolean close() {
		// TODO Auto-generated method stub
		return true;
	}

	@Override
	public Node getDisplay() {
		// TODO Auto-generated method stub
		return bp_;
	}

	// private SplitPane sp_ = new SplitPane();
	BorderPane bp_ = new BorderPane();
	private VisCanvas vis_canvas_ = new VisCanvas();
	private BorderPane canvas_pane_ = new BorderPane();
	private Slider adjust_force_slider_ = new Slider(1.0, 100, 10);
	private ToggleSwitch stop_forces_ = new ToggleSwitch("Stop Vertices");
	private ToggleSwitch show_node_ids_ = new ToggleSwitch("All Vertex IDs");
	private ToggleSwitch show_relationships_ = new ToggleSwitch("All Relationships");
	private ToggleSwitch show_legend_ = new ToggleSwitch("Legend");
	private Button choose_file_btn_ = new Button("Choose File");
	@SuppressWarnings("unused")
	private ProVisCtrl pro_vis_ctrl_; // Keep a reference, not sure if the object will still exist if not. TODO Move
										// ProVisCtrl to over here
}
