package Final.s105502054;


import javafx.animation.AnimationTimer;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;

import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;

import javafx.scene.text.Text;
import javafx.util.Duration;


public class mission1Controller {

	private GameManager gamemanger;
	@FXML
	private Canvas canvas;
	@FXML
	private Text score;
    @FXML
    private Text chp1;

    @FXML
    private Text chp2;
    @FXML
    private ImageView list;
    @FXML
    private ImageView bbackground;

	private AnimationTimer update;
	static storeroom store[] = new storeroom[100000];
	static storeroom store1[] = new storeroom[100000];

	static int x = 280, y = 0, mx = 950, my = 710, hp = 0, rint = 1000;
	static int money = 10000;

	@FXML
	private void initialize() {
		
		gamemanger = new GameManager(canvas.getGraphicsContext2D());
		update = new AnimationTimer() {

			public void handle(long nowtime) {
				if(initialController.aaa==1){		//the game will start only after you clicked the start button

				canvas.getGraphicsContext2D().clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
				score.setText("$" + String.valueOf(money));					//show up the information of money,hp
				chp1.setText("hp " + String.valueOf(store1[0].hp));
				chp2.setText("hp " + String.valueOf(store[0].hp));
				



				gamemanger.detect();
				gamemanger.draw(nowtime);
				gamemanger.move();
				if(mission1Controller.store1[0].hp<=0)			//when your castle fallen
				{
					bbackground.setImage(ImageUtility.lose);
					
				}
				if(mission1Controller.store[0].hp<=0)			//when their castle fallen
				{
					bbackground.setImage(ImageUtility.Win);
					
				}
				}
			}

		};
		update.start();
		EventHandler<ActionEvent> eventHandler1 = e -> {


			
			int rtype = (int) (Math.random() * 4);		//random the monster type will appear next
			if (rtype == 1) {

				store[GameManager.array] = new storeroom(1, hp+50, mx, my, true, ImageUtility.soldier,2);
				GameManager.array++;
			}
			if (rtype == 2) {
				store[GameManager.array] = new storeroom(2, hp+50, mx, my, true, ImageUtility.runner,3);
				GameManager.array++;

			}
			if (rtype == 3) {
				store[GameManager.array] = new storeroom(3, hp+50, mx, my, true, ImageUtility.dragon,4);
				GameManager.array++;
			}

		};
		
		Timeline animation1 = new Timeline(new KeyFrame(Duration.millis(rint), eventHandler1));
		animation1.setCycleCount(Timeline.INDEFINITE);
		animation1.play();
		EventHandler<ActionEvent> eventHandler = e -> {
			hp+=10;															//every 60s,monster will be stronger
			rint -= 50;


		};
		Timeline animation = new Timeline(new KeyFrame(Duration.millis(60000), eventHandler));

		animation.setCycleCount(Timeline.INDEFINITE);						//call background music repeat
		animation.play();


	
	}


	public void setScene(Scene scene1) {
		
		gamemanger.playMusic1();
		store[GameManager.array] = new storeroom(4, 5000, 1000, 580, true, ImageUtility.castle1,7);	//your castle
		
		GameManager.array++;
		
		store1[GameManager.array1] = new storeroom(1, 5000, 0, 580, true, ImageUtility.castle,6);// their castle
		
		GameManager.array1++;

		scene1.setOnKeyPressed(e -> {			//call your hero

			if (e.getCode() == KeyCode.Z) {
				if (money >= 500) {
					store1[GameManager.array1] = new storeroom(2, 150, x, 660, true, ImageUtility.soldier1,2);
					GameManager.array1++;
					money -= 500;
				}

			}
			if (e.getCode() == KeyCode.X) {
				if (money >= 1000) {
					store1[GameManager.array1] = new storeroom(3, 150, x, 660, true, ImageUtility.knight,3);
					GameManager.array1++;
					money -= 500;

				}

			}
			if (e.getCode() == KeyCode.C) {
				if (money >= 1500) {
					store1[GameManager.array1] = new storeroom(4, 150, x, 660, true, ImageUtility.giant,4);
					GameManager.array1++;
					money -= 500;
					
					
				}

			}


		});

	}

}
