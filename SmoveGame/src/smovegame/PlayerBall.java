package smovegame;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;

public class PlayerBall {
    private static final int DIAMETER = 40;
    int playerno;
    boolean lflag=false,rflag=false,uflag=false,dflag=false;
    int x = 220,y=220;
    int xp=1,yp=1;
    private Game game;

    public PlayerBall(Game game,int playerno) {
        this.game = game;
        this.playerno=playerno;
        x+=550*this.playerno;
    }

    public void move() {
        
    }

    private boolean collision() {
	//return game.racquet.getBounds().intersects(getBounds());
        return false;
    }

    public void paint(Graphics2D g) {
        g.setColor(Color.WHITE);
	g.fillOval(x, y, DIAMETER, DIAMETER);
    }
	
    public Rectangle getBounds() {
        return new Rectangle(x+3, y+3, DIAMETER-6, DIAMETER-6);
    }
    
    public void keyReleased(KeyEvent e) {
        if ((e.getKeyCode() == KeyEvent.VK_LEFT && playerno==1) || (e.getKeyCode() == KeyEvent.VK_A && playerno==0)){
                lflag=false;
        }
        else if ((e.getKeyCode() == KeyEvent.VK_RIGHT && playerno==1) || (e.getKeyCode() == KeyEvent.VK_D && playerno==0)){
                rflag=false;
        }
        else if ((e.getKeyCode() == KeyEvent.VK_UP && playerno==1) || (e.getKeyCode() == KeyEvent.VK_W && playerno==0)){
                uflag=false;
        }
        else if ((e.getKeyCode() == KeyEvent.VK_DOWN && playerno==1) || (e.getKeyCode() == KeyEvent.VK_S && playerno==0)){
                dflag=false;
        }
        
    }

    public void keyPressed(KeyEvent e) {
        if ((e.getKeyCode() == KeyEvent.VK_LEFT && playerno==1) || (e.getKeyCode() == KeyEvent.VK_A && playerno==0)){
            if(!lflag){
                lflag=true;
                if(xp!=0){
                    x-=60;
                    xp-=1;
                }
            }
        }    
        else if ((e.getKeyCode() == KeyEvent.VK_RIGHT && playerno==1) || (e.getKeyCode() == KeyEvent.VK_D && playerno==0)){
            if(!rflag){
                rflag=true;
                if(xp!=2){
                    x+=60;
                    xp+=1;
                }
                    
            }
        }
        else if ((e.getKeyCode() == KeyEvent.VK_UP && playerno==1) || (e.getKeyCode() == KeyEvent.VK_W && playerno==0)){
            if(!uflag){
                uflag=true;
                if(yp!=0){
                    y-=60;
                    yp-=1;
                }
            }
        }
        else if ((e.getKeyCode() == KeyEvent.VK_DOWN && playerno==1) || (e.getKeyCode() == KeyEvent.VK_S && playerno==0)){
            if(!dflag){
                dflag=true;
                if(yp!=2){
                    y+=60;
                    yp+=1;
                }
            }
        }
        
    }
}