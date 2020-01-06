package smovegame;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.util.Random;

public class BlackBall {
    private static final int DIAMETER = 40;
    private static final int SPEED=2;
    int playerno;
    int[] pos={160,220,280};
    int x,y,dir;
    private Game game;
    
    public BlackBall(Game game,int playerno){
        this.game=game;
        this.playerno=playerno;
        initialize();
    }
    
    private void initialize(){
        Random random = new Random();
        dir=random.nextInt(4);
        if(dir==0){//top to bottom
            x=pos[random.nextInt(3)]+550*playerno;
            y=-40;
        }
        else if(dir==1){//bottom to top
            x=pos[random.nextInt(3)]+550*playerno;
            y=500;
        }
        else if(dir==2){//left to right
            x=-40+550*playerno;
            y=pos[random.nextInt(3)];
        }
        else{//bottom to top
            x=500+550*playerno;
            y=pos[random.nextInt(3)];
        }
    }
    
    public void move(){
        
        if(collision()){
            game.gameover[playerno]=true;
            return;
        }
        
        if(y>500 || y<-40 || x<-40+550*playerno || x>500+550*playerno)
            initialize();
        
        if(dir==0)y+=SPEED;
        else if(dir==1)y-=SPEED;
        else if(dir==2)x+=SPEED;
        else x-=SPEED;
    }
    
    public void paint(Graphics2D g) {
        g.setColor(Color.BLACK);
	g.fillOval(x, y, DIAMETER, DIAMETER);
    }
    
    public Rectangle getBounds(){
        return new Rectangle(x+3,y+3,DIAMETER-6,DIAMETER-6);
    }
    
    public boolean collision(){
        return game.playerBall[playerno].getBounds().intersects(getBounds());
    }
}
