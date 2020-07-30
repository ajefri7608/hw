package Final.s105502054;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;

import javafx.stage.Stage;


public class Main  extends Application{

	@Override
	public void start(Stage primaryStage) throws Exception {
		FXMLLoader fxmlLoader =new FXMLLoader(getClass().getResource("initial.fxml"));
		initialController initialController = new initialController();
		fxmlLoader.setController(initialController);
		Parent root =fxmlLoader.load();
		Scene scene=new Scene(root,1200, 800);
		
		

		FXMLLoader fxmlLoader1 =new FXMLLoader(getClass().getResource("mission1.fxml"));
		mission1Controller mission1controller=new mission1Controller();
	   fxmlLoader1.setController(mission1controller);
	   Parent root1 = fxmlLoader1.load();
	   Scene scene1=new Scene(root1,1200,800);
	   
		primaryStage.setTitle("Final");
		initialController.setStage ( primaryStage );
		initialController.setnextscene1 ( scene1 );
		mission1controller.setScene(scene1);
		primaryStage.setScene(scene);
		primaryStage.show();
		
	   
	   
	}
	public static void main(String[] args) {
		launch(args);
	}
	

}
