package Final.s105502054;

import java.io.File;


import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;

import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;


class storeroom {
	int type;
	int hp;
	int x1;
	int y1;
	boolean move;
	Image image;
	int type1;

	storeroom(int type, int hp, int x1, int y1, boolean move, Image image,int type1) {
		this.type = type;
		this.hp = hp;
		this.x1 = x1;
		this.y1 = y1;
		this.move = move;
		this.image = image;				//for get width
		this.type1 = type1;				//for calculate the counter relationship

	}
}

public class GameManager {
	static int array = 0, array1 = 0;
	static int temp;

	private GraphicsContext gc;
	private double playerx, playery;
	private MediaPlayer mediaplayer;
	private MediaPlayer mediaplayer1;
	private long pretime;

	public void draw(long nowtime) {

		double deltaTime = (nowtime - pretime) / 1e9;

		pretime = nowtime;
		

		for (int a = 0; a <= array - 1; a++) {

			if (mission1Controller.store[a].hp <= 0) {
				if (mission1Controller.store[a].type == 1)	//when monster dead,u will earn money
					mission1Controller.money += 800;
				if (mission1Controller.store[a].type == 2)
					mission1Controller.money += 800;
				if (mission1Controller.store[a].type == 3)
					mission1Controller.money += 800;
				mission1Controller.store[a].type = 6;
				mission1Controller.store[a].x1+=1000;
			}
			if(mission1Controller.store[a].hp > 0){		//if monster not dead,draw it
			if (mission1Controller.store[a].type == 1) {
				gc.drawImage(ImageUtility.soldier, mission1Controller.store[a].x1, mission1Controller.store[a].y1);
			}
			if (mission1Controller.store[a].type == 2) {
				gc.drawImage(ImageUtility.runner, mission1Controller.store[a].x1, mission1Controller.store[a].y1);

			}
			if (mission1Controller.store[a].type == 3) {
				gc.drawImage(ImageUtility.dragon, mission1Controller.store[a].x1, mission1Controller.store[a].y1);

			}
			if (mission1Controller.store[a].type == 4) {
				gc.drawImage(ImageUtility.castle1, mission1Controller.store[0].x1, mission1Controller.store[0].y1);

			}
			if (mission1Controller.store[a].move == false) {	//if object collision,show up the effect
				if (mission1Controller.store[a].hp > 0) {
					
					gc.drawImage(ImageUtility.boom, mission1Controller.store[a].x1 - 50,
							mission1Controller.store[a].y1 - 210);


						mission1Controller.store[a].hp-=1;
					
				}
				mission1Controller.store[0].move=true;
			}
		}

		}
		for (int b = 0; b <= array1 - 1; b++) {
			if (mission1Controller.store1[b].hp <= 0) {	//if object dead,stop draw it

				mission1Controller.store1[b].type = 10;
				mission1Controller.store1[b].x1+=1000;
			}
			if(mission1Controller.store1[b].hp > 0){	//if object not dead,continue draw it
			if (mission1Controller.store1[b].type == 1) {
			gc.drawImage(ImageUtility.castle, mission1Controller.store1[0].x1, mission1Controller.store1[0].y1);
			}
			if (mission1Controller.store1[b].type == 2) {
				gc.drawImage(ImageUtility.soldier1, mission1Controller.store1[b].x1, mission1Controller.store1[b].y1);
			}
			if (mission1Controller.store1[b].type == 3) {
				gc.drawImage(ImageUtility.knight, mission1Controller.store1[b].x1, mission1Controller.store1[b].y1);
			}
			if (mission1Controller.store1[b].type == 4) {
				gc.drawImage(ImageUtility.giant, mission1Controller.store1[b].x1, mission1Controller.store1[b].y1);
			}

			if (mission1Controller.store1[b].move == false) {	//if the object is collision,hp decrease
				if (mission1Controller.store1[b].hp > 0)
				{
					gc.drawImage(ImageUtility.boom, mission1Controller.store1[b].x1 + 50,
							mission1Controller.store1[b].y1 - 210);
					
				}
				
				if(mission1Controller.store1[b].type==mission1Controller.store1[b].type1)
				{
					mission1Controller.store1[b].hp-=1;
					
				}
				if(mission1Controller.store1[b].type!=mission1Controller.store1[b].type1)
					{
					mission1Controller.store1[b].hp-=10;}
				mission1Controller.store1[0].move=true;
			}
		}

		}

	}

	public void detect() {					//detect the object collision,and detect who were collision,calculate their counter relationship
		for (int a1 = 0; a1 <= array - 1; a1++) {
			for (int b1 = 0; b1 <= array1 - 1; b1++) {
				if (mission1Controller.store[a1].x1 >= mission1Controller.store1[b1].x1
						&& mission1Controller.store[a1].x1 <= mission1Controller.store1[b1].x1
								+ mission1Controller.store1[b1].image.getWidth()
						) {
					temp=mission1Controller.store[a1].type1;		
					mission1Controller.store[a1].type1=mission1Controller.store1[b1].type1;
					mission1Controller.store1[b1].type1=temp;
					mission1Controller.store[a1].move = false;
					mission1Controller.store1[b1].move = false;
					

				}

			}
		}
	}

	public void move() {	//if the object is not collision,move the object forward
		for (int a2 = 1; a2 <= array - 1; a2++) {

			if (mission1Controller.store[a2].move != false) {

				
				mission1Controller.store[a2].x1 -= 2;

			}
			mission1Controller.store[a2].move = true;
		}
		for (int b2 = 1; b2 <= array1 - 1; b2++) {

			if (mission1Controller.store1[b2].move != false) {

				mission1Controller.store1[b2].x1 += 2;

			}
			mission1Controller.store1[b2].move = true;

		}
	}

	public GameManager(GraphicsContext a) {
		mediaplayer = new MediaPlayer(new Media(new File("sound/background.mp3").toURI().toString()));
		mediaplayer1 = new MediaPlayer(new Media(new File("sound/sound.mp3").toURI().toString()));
		gc = a;

		playerx = 0;
		playery = 580;

	}

	public void playMusic1() {
		
		mediaplayer.play();
		 mediaplayer.setCycleCount(MediaPlayer.INDEFINITE);
	}

	public void playMusic2() {
		
		mediaplayer1.stop();
		mediaplayer1.play();
	}

}
