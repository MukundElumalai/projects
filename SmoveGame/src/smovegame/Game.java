package smovegame;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

@SuppressWarnings("serial")
public class Game extends JPanel {
    PlayerBall[] playerBall = new PlayerBall[2];
    ScoreBall[] scoreBall = new ScoreBall[2];
    BlackBall[][] blackBall = new BlackBall[2][5];
    boolean[] gameover={false,false};
    
    int score[]={0,0},level[]={1,1},cap[]={2,2},ballCount[]={0,0};

    public Game(){
        setBackground(Color.PINK);
        
        
        addKeyListener(new KeyListener() {
	@Override
        public void keyTyped(KeyEvent e) {
            //do nothing
	}
        
        @Override
	public void keyReleased(KeyEvent e) {
            playerBall[0].keyReleased(e);
            playerBall[1].keyReleased(e);
        }
		
        @Override
        public void keyPressed(KeyEvent e) {
            playerBall[0].keyPressed(e);
            playerBall[1].keyPressed(e);
	}
        });
        setFocusable(true);
    }
    
    public void createBB(int i){
        MyRunnable runnable=new MyRunnable(this,i);
        runnable.start();
    }
        
    private void move() {
        if(!gameover[0])
            for(int i=0;i<ballCount[0];i++)
                blackBall[0][i].move();
        if(!gameover[1])
            for(int i=0;i<ballCount[1];i++)
                blackBall[1][i].move();
    }

    @Override
    public void paint(Graphics g) {
            
        super.paint(g);
	Graphics2D g2d = (Graphics2D) g;
        
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);
        
        
        
        g2d.setStroke(new BasicStroke(5));
        g2d.setColor(Color.WHITE);
        g2d.drawRoundRect(150, 150, 180, 180, 60, 60);
        g2d.setStroke(new BasicStroke(2));
        g2d.setColor(Color.WHITE);
        g2d.drawLine(210, 150, 210, 330);
        g2d.setColor(Color.WHITE);
        g2d.drawLine(270, 150, 270, 330);
        g2d.setColor(Color.WHITE);
        g2d.drawLine(150, 210, 330, 210);
        g2d.setColor(Color.WHITE);
        g2d.drawLine(150, 270, 330, 270);
        
        g2d.setStroke(new BasicStroke(5));
        g2d.setColor(Color.WHITE);
        g2d.drawRoundRect(700, 150, 180, 180, 60, 60);
        g2d.setStroke(new BasicStroke(2));
        g2d.setColor(Color.WHITE);
        g2d.drawLine(760, 150, 760, 330);
        g2d.setColor(Color.WHITE);
        g2d.drawLine(820, 150, 820, 330);
        g2d.setColor(Color.WHITE);
        g2d.drawLine(700, 210, 880, 210);
        g2d.setColor(Color.WHITE);
        g2d.drawLine(700, 270, 880, 270);

	
        if(!gameover[0]){
            playerBall[0].paint(g2d);
            scoreBall[0].paint(g2d);
            for(int i=0;i<ballCount[0];i++)
                blackBall[0][i].paint(g2d);
        }
        if(!gameover[1]){
            playerBall[1].paint(g2d);
            scoreBall[1].paint(g2d);
            for(int i=0;i<ballCount[1];i++)
                blackBall[1][i].paint(g2d);
        }
        
        g2d.setColor(Color.WHITE);
        g2d.fillRect(500, 0, 50, 500);
    }
        
    public void gameOver(String string) {
        repaint();
        if(string.equals("victory")){
            if(score[0]==50)
                string="player 1 wins";
            else
                string="player 2 wins";
        }
        JOptionPane.showMessageDialog(this, string, string, JOptionPane.YES_NO_OPTION);
	System.exit(0);
    }
    
    public void start(){
        JOptionPane.showMessageDialog(this, "start", "start", JOptionPane.YES_NO_OPTION);
    }

    public static void main(String[] args) throws InterruptedException {

        JFrame frame = new JFrame("Smove");
        Game game = new Game();
        
        for(int i=0;i<2;i++){
            game.playerBall[i]=new PlayerBall(game,i);
            game.scoreBall[i]=new ScoreBall(game,i);
        }
        
        frame.add(game);
        frame.setSize(1050, 500);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        game.start();
        
        
        game.createBB(0);
        game.createBB(1);
        
        while (true) {
            game.move();
            if(game.gameover[0] && game.gameover[1]){
                String s="Draw";
                if(game.score[1]<game.score[0])
                    s="Player 1 wins";
                else if(game.score[1]>game.score[0])
                    s="Player 2 wins";
                game.gameOver(s);
            }
            game.repaint();
            Thread.sleep(10);
        }
        
    }
}



class MyRunnable extends Thread{
    private Game game;
    private int playerno;
    
    MyRunnable(Game game,int playerno){
        this.game=game;
        this.playerno=playerno;
    }
    
    @Override
    public void run(){
        for(int i=game.ballCount[playerno];i<game.cap[playerno];i++){
            try {
                this.sleep(1000);
            } catch (InterruptedException ex) {
                Logger.getLogger(MyRunnable.class.getName()).log(Level.SEVERE, null, ex);
            }
            game.blackBall[playerno][i]=new BlackBall(game,playerno);
            game.ballCount[playerno]++;
        }
    }
}