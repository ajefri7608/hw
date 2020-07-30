package Final.s105502054;

import Final.s105502054.ImageUtility;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;;

public class initialController {

    @FXML
    private Button start;

    @FXML
    private Button quit;
    
    @FXML
    private ImageView background;
    
    static int aaa=0;
	Scene nextscene1;
	Stage stage;

    
    public void setnextscene1(Scene nextscene1){
    	this.nextscene1=nextscene1;
    }
	public void setStage(Stage stage){
		this.stage=stage;
	}
	@FXML
	private void initialize(){
		
		start.setOnAction(e->{
			stage.setScene(nextscene1);
			aaa=1;
		});
		quit.setOnAction(e->{stage.close();});
		background.setImage(ImageUtility.background);
		
		
	}
}

