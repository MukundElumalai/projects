package smovegame;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.util.Random;

public class ScoreBall {
    private static final int SIDE = 20;
    int playerno;
    
    int x=0,y=0,xp,yp;
    private Game game;
    
    public ScoreBall(Game game,int playerno){
        this.game=game;
        this.playerno=playerno;
        move();
    }
    
    private void move() {
        Random random=new Random();
        do{
            xp=random.nextInt(3);
            yp=random.nextInt(3);        
        }while(xp==game.playerBall[playerno].xp && yp==game.playerBall[playerno].yp);
        x=170+xp*60+550*playerno;
        y=170+yp*60;
    }

    private boolean collision() {
	return game.playerBall[playerno].getBounds().intersects(getBounds());
    }

    public void paint(Graphics2D g) {
        g.setFont(new Font("Serif", Font.BOLD, 20));     
        g.setColor(Color.WHITE);
        g.drawString("SCORE : "+game.score[playerno], 15+550*playerno, 25);
        
        if(collision()){
            game.score[playerno]+=1;
            game.level[playerno]=(int)game.score[playerno]/10+1;
            if(game.cap[playerno]<game.level[playerno]+1){
                game.cap[playerno]=game.level[playerno]+1;
                game.createBB(playerno);
            }
            if(game.score[playerno]==50)
                game.gameOver("victory");
            move();
        }
        g.setColor(Color.BLUE);
	g.fillRoundRect(x, y, SIDE, SIDE,10,10);
    }
	
    public Rectangle getBounds() {
        return new Rectangle(x, y, SIDE, SIDE);
    }
    
}
