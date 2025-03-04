#include <iostream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <sstream>
#include <fstream>
#include <SDL2/SDL_mixer.h>
#include <ctime>


using namespace std;


string tostring(int number);
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian);
void window_color(SDL_Renderer *Renderer, int R, int G, int B);
void texture(SDL_Renderer *m_renderer,double xp,double yp,string addressOfImage,int width,int height);
void main_menu(SDL_Renderer *m_renderer,int Width,int Height,bool mainmenu_animation,bool theme1, bool theme2);
void text(SDL_Renderer * m_renderer,int xp,int yp,int width, int height,int R,int G,int B,int Size,string Message);
void setting(SDL_Renderer *m_renderer,int x_setting_L, int x_setting_R, int y_setting_U,int y_setting_D,int a);
void league(SDL_Renderer * m_renderer,string players[],string wins[],string losses[],string goals[],int n);
void start(SDL_Renderer * m_renderer);
void typing(SDL_Renderer * m_renderer,SDL_Event * e,string &current_player,int x_p);
void maingame(SDL_Renderer *m_renderer);
void ad(SDL_Renderer *m_renderer,int &ad_x1,int ad_h,int ad_w);
void save_info(int &current_goals1,int &current_goals2,string players[],string winner,string goals[],string losses[],string wins[],int &n,string current_player1,string current_player2);
int ad_x1=0;
int ad_h=70;
int ad_w=1930;




int main( int argc, char * argv[] )
{
     const int Width = 1280,Height = 800 ;

    //Initialization of SDL windows
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER |SDL_INIT_AUDIO;//SDL_INIT_AUDIO Initial Audio for the project
    TTF_Init(); //This Line added for defining new font


    Uint32 WND_flags = SDL_WINDOW_SHOWN ;//| SDL_WINDOW_FULLSCREEN_DESKTOP;//SDL_WINDOW_BORDERLESS ;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    //Texture for loading image
    Mix_OpenAudio(22000,MIX_DEFAULT_FORMAT,2,2048); //Define Audio type //MIX_DEFAULT_FREQUENCY

    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( Width, Height, WND_flags, &m_window, &m_renderer );
    //Pass the focus to the drawing window
    SDL_RaiseWindow(m_window);
    //Get screen resolution
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    string backsound = "Waka Waka.mp3"; //Background sound Address
    string cheer = "cheering1.wav"; //Chunk sound Address
    Mix_Music *GameSound = Mix_LoadMUS(backsound.c_str()); //Load background sound
    Mix_Chunk *collision = Mix_LoadWAV(cheer.c_str()); //Load sound for wall collision
    Mix_PlayMusic(GameSound,-1); //Play the sound.  -1 means play it till the end


    // Clear the window with a black background
    //SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear( m_renderer );

    // Show the window
    SDL_RenderPresent( m_renderer );
    SDL_Event *e = new SDL_Event();


    int x_setting_L= 585, x_setting_R= 725, y_setting_U= 265, y_setting_D= 435,a_setting = 100 ; //setting info

    double  height_menu= 100,width_menu= 300, y_menu2 = 280;//menu info
    double y_menu3 = 400, y_menu4 = 520, y_menu5 = 640,x_menu = ((Width - width_menu) / 2);//menu info
    bool theme1 = true, theme2 = false;//menu info

    int x,y;//mouse location

    int n = 0, i = -1;//players number
    int player1_x=400,player1_y=500,player2_x=800,player2_y=500,ball_x=Width/2-20,ball_y=500,g=10,ball_v=1;
    float t=0;
    string players[100], goals[100], wins[100], losses[100],current_player1="",current_player2="";//players info for league table
    string player1_ch = "", player2_ch = "", ball = "",temp="",ending_type = "5goal";
    bool typed = false;
    double namet1_x = 40,namet2_x = 1150,t_y = 30, t_h = 19, namet1_w = 90,namet2_w=90,scoret_w = 15,scoret1_x = 185,scoret2_x=1080;
    double timet_x = 622,timet_w=36,timet_h = 36;




    for(int j = 0; j < 100 ; j++)
    {
        goals[j]="0";
        losses[j]="0";
        wins[j]="0";
    }

    bool entrance_animation = true;
    bool mainmenu = true, mainmenu_animation = true, start2 = false, setting4 = false, league3 = false, game =true;
    bool main_game = false;
    while(game)
    {
        n = 0;
        string filename = "records.txt";
        ifstream input;
        input.open(filename.c_str());
        if(input.good())
        {
            while(!input.eof())
                if(input.good())
                {
                    input>>players[n];
                    input>>wins[n];
                    input>>losses[n];
                    input>>goals[n];
                    n++;
                }
        }
        else
            cout<<"error...";
        input.ignore();
        input.close();
        n--;
      //  cout<<"n : "<< n<<endl;
        int current_goal1=0,current_goal2=0;
        x=0,y=0;
        while(mainmenu)
        {
            player1_ch = "", player2_ch = "", ball = "",temp="",current_player1="",current_player2="",current_goal1=0,current_goal2=0;
            main_menu(m_renderer,Width,Height,mainmenu_animation,theme1, theme2);
            mainmenu_animation = false;
            main_menu(m_renderer,Width,Height,mainmenu_animation,theme1, theme2);
            SDL_GetMouseState(&x, &y);
            e -> type = 0;
            SDL_PollEvent(e);
            if(e-> type==SDL_MOUSEBUTTONDOWN)
            {
                if(x > x_menu && x < x_menu + width_menu && y > y_menu2 && y < y_menu2 + height_menu)
                {
                    start2 = true;
                    mainmenu = false;
                    break;
                }
                else if(x > x_menu && x < x_menu + width_menu && y > y_menu3 && y < y_menu3 + height_menu)
                {
                    league3 = true;
                    mainmenu = false;
                    break;
                }
                else if(x > x_menu && x < x_menu + width_menu && y > y_menu4 && y < y_menu4 + height_menu)
                {
                    setting4 = true;
                    mainmenu = false;
                    break;
                }
                else if(x > 740 && x < 910 && y > 210 && y < 255)
                {
                    window_color(m_renderer,0,0,0);
                    texture(m_renderer,0,0,"aboutus.JPEG",Width,Height);
                    SDL_RenderPresent(m_renderer);
                    while(true)
                    {
                        e->type = 0;
                        SDL_PollEvent(e);
                        if(e -> type == SDL_KEYDOWN && e -> key.keysym.sym == SDLK_ESCAPE)
                            break;

                    }
                }
                else if(x > x_menu && x < x_menu + width_menu && y > y_menu5 && y < y_menu5 + height_menu)
                {
                    start2 = false, setting4 = false, league3 = false, game = false, mainmenu = false;
                    break;
                }
            }
            else if(e-> type == SDL_QUIT)
            {
                start2 = false, setting4 = false, league3 = false, game = false, mainmenu = false;
                break;
            }

        }
        window_color(m_renderer,0,0,0);
        if(start2)
        {
            start(m_renderer);
            SDL_RenderPresent(m_renderer);
            player1_ch = "", player2_ch = "", ball = "",temp="",current_player1="",current_player2="",current_goal1=0,current_goal2=0;
        }
        while(start2)
        {
            int x_p1 = 240, x_p2 = 900;
            int x_rm = 760, x_rw = 990, x_bm = 360, x_bw = 100, y_ch = 190, height_ch = 200, width_rm = 160, width_rw = 140, width_bw = 170,width_bm = 120;
            int L = 100, width_b = 130, x_b1 = 100, x_b2 = x_b1 + L + width_b, x_b3 = x_b1, x_b4 = x_b2, y_b12 = 465,y_b34 = y_b12+width_b + 50, height_b = 130;
            int x_90or5 = 580,y_90 = y_b12 + 100,w_90or5 = 120, h_90 = 60;
            int y_5 = y_b12 + 200,h_5 = 90;

            e -> type = 0;
            SDL_PollEvent(e);
            if((e -> type == SDL_KEYDOWN && e -> key.keysym.sym == SDLK_ESCAPE)  || e -> type == SDL_QUIT)
            {
                start2 = false;
                mainmenu = true;
                typed = false;
                break;
            }
            e->type = 0;
            SDL_PollEvent(e);
            SDL_GetMouseState(&x,&y);
            if(e -> type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&x,&y);
                if(x > x_rm && x < x_rm + width_rm && y > y_ch && y < y_ch + height_ch)
                    player2_ch = "rm_head.png";
                else if(x > x_rw && x < x_rw + width_rw && y > y_ch && y < y_ch + height_ch)
                    player2_ch = "rw_head.png";
                if(x > x_bw && x < x_bw + width_bw && y > y_ch && y < y_ch + height_ch)
                    player1_ch = "bw_head.png";
                else if(x > x_bm && x < x_bm + width_bm && y > y_ch && y < y_ch + height_ch)
                    player1_ch = "bm_head.png";
                if(x > x_b1 && x < x_b1 + width_b && y > y_b12 && y < y_b12 + height_b)
                    temp = "ball1";
                else if(x > x_b2 && x < x_b2 + width_b && y > y_b12 && y < y_b12 + height_b)
                    temp = "ball2";
                else if(x > x_b3 && x < x_b3 + width_b && y > y_b34 && y < y_b34 + height_b)
                    temp = "ball3";
                else if(x > x_b4 && x < x_b4 + width_b && y > y_b34 && y < y_b34 + height_b)
                    temp = "ball4";
                else if(x > x_90or5 && x < x_90or5 + w_90or5 && y > y_90 && y < y_90 + h_90)
                    ending_type = "90s";
                else if(x > x_90or5 && x < x_90or5 + w_90or5 && y > y_5 && y < y_5 + h_5)
                    ending_type = "5goal";
                if(x > 50 && x < 540 && y > 10 && y < 160)
                {

                    while(true)
                    {
                        SDL_PollEvent(e);
                        if(e -> type == SDL_KEYDOWN)
                            typing(m_renderer,e,current_player1,x_p1);
                        e -> type = 0;
                        if(e->key.keysym.sym == SDLK_SPACE)
                        {
                            break;
                        }
                        SDL_Delay(10);
                    }
                    typed = true;

                }
                else if(x > 700 && x < 1190 && y > 10 && y < 160)
                {

                    while(true)
                    {
                        SDL_PollEvent(e);
                        if(e -> type == SDL_KEYDOWN)
                        {
                            typing(m_renderer,e,current_player2,x_p2);
                        }
                        e -> type = 0;
                        if( e->key.keysym.sym == SDLK_SPACE)
                        {
                            break;
                        }

                        SDL_Delay(10);
                    }
                    typed = true;
                }
                if(e -> type == SDL_MOUSEBUTTONDOWN)
                {
                    SDL_GetMouseState(&x,&y);
                    if(x > 800 && x < 1250 && y > 465 && y < 765)
                    {
                        start2 = false;
                        main_game = true;
                        //cout<<endl<<"im working..."<<endl;
                        break;
                    }

                }
            }
            SDL_Delay(50);
          //  cout<<player1_ch<<endl<<player2_ch<<endl<<temp<<endl<<current_player1<<endl<<current_player2<<endl<<ending_type<<endl;

        }
        if(league3)
        {
            window_color(m_renderer,0,0,0);
            texture(m_renderer,0,0,"mainmenubg1.png",1280,800);
        }
        while(league3)
        {
            league(m_renderer,players,wins,losses,goals,n);
            e -> type = 0;
            SDL_PollEvent(e);
            if((e -> type == SDL_KEYDOWN && e -> key.keysym.sym == SDLK_ESCAPE ) || e -> type == SDL_QUIT)
            {
                league3 = false;
                mainmenu = true;
                break;
            }
        }
        if(setting4)
        {
            setting(m_renderer,x_setting_L,x_setting_R,y_setting_U,y_setting_D,a_setting);
            SDL_RenderPresent(m_renderer);
        }
        while(setting4)
        {
            e -> type = 0;
            SDL_GetMouseState(&x, &y);
            SDL_PollEvent(e);
            if((e -> type == SDL_KEYDOWN && e -> key.keysym.sym == SDLK_ESCAPE ) || e -> type == SDL_QUIT)
            {
                setting4 = false;
                mainmenu = true;
                break;
            }
            else if(e -> type == SDL_MOUSEBUTTONDOWN)
            {
                if(x > x_setting_L && x < x_setting_L + a_setting && y > y_setting_D && y < y_setting_D + a_setting)
                {
                    theme1 = true;
                    theme2 = false;
                    mainmenu_animation = true;
                }
                else if(x > x_setting_R && x < x_setting_R + a_setting && y > y_setting_D && y < y_setting_D + a_setting)
                {
                    theme1 = false;
                    theme2 = true;
                    mainmenu_animation = true;
                }
            }
            SDL_Delay(20);

        }
        double j = 1,ball_vy=1,ball_y=300,ball_vx=0,ball_ay=2;
        double h_head=60,w_head=60;//player2
        double w_body = 170,h_body = 146;//player1
        double player1_x=350,player1_y=474,player2_x=755,player2_y=474,ball_x=Width/2-20,este = 0.3;
        double x_goal_left=-60,y_goal_left = 390,w_goal= 209, h_goal = 250;//Goal left
        double x_goal_right=1128,y_goal_right = 390;//Goal right
        double walk_animation=5;
        double y_audience1 = 390,h_audience = 30,x_audience = 180;
        double y_audience2 =305;
        double walk=10,jump_1=-20,jump_2=-20,g=1;
        bool running=false,gamestart=true,shoot1=false,shoot2=false,jump1=false,jump2=false;
        double zarib=0.5;
        int k1=1,k2=1,zamin = 620;
        bool goal1 = false, goal2 = false;
        int x_sb= 365, y_sb = 0,h_sb = 75, w_sb =550,x_name1 = 40,y_name = 33, x_name2 = 1150, w_name = 90,h_name = 19;
        int x_score1= 185, x_score2 = 1080,y_score = 33,w_score=15,h_score = 19;
        bool pause = false;
        bool powerline1_full = false,powerline2_full = false;
        int p1=1,p2=1,extra_power1=0,extra_power2=0,pu1=0,pu2=0;
        int c=1,t_thunder=0,t_rock=0;
        bool thunder_power=false,rock_power = false;
        double x_rock = 1080,y_rock = 410,w_rock = 130,h_rock = 225;
        current_goal1 = 0;
        current_goal2 = 0;


        if(main_game)
        {
            window_color(m_renderer,0,0,0);
        }
        while(main_game)
        {
            string powerline1="power11.png";
            string powerline2="power21.png";
            double game_menu_x=15,game_menu_y=110,game_menu_w=55,game_menu_h=55;
            double nameboard1_x=15,nameboard1_y=15,nameboard1_w=150,nameboard1_h=55;
            double nameboard2_x=1115,nameboard2_y=15,nameboard2_w=150,nameboard2_h=55;
            double score1_x=nameboard1_x+nameboard1_w,score1_y=nameboard1_y,score1_w=nameboard1_h,score1_h=nameboard1_h;
            double score2_x=nameboard2_x-nameboard1_h,score2_y=nameboard1_y,score2_w=nameboard1_h,score2_h=nameboard1_h;
            double timeboard_x=640-(nameboard1_h+15)/2,timeboard_y=nameboard1_y,timeboard_w=nameboard1_h+15,timeboard_h=nameboard1_h+15;
            double powerline1_x=nameboard1_x,powerline1_y=nameboard1_y+nameboard1_h+5,powerline1_w=205,powerline1_h=26;
            double powerline2_x=nameboard2_x+nameboard1_w-205,powerline2_y=nameboard2_y+nameboard2_h+5,powerline2_w=205,powerline2_h=26;


            double w_ball = 40, h_ball = 40;
            double x1 = 219,x2=893;
            int q = 1;
            if(entrance_animation)
            {
                Mix_PlayChannel(-1,collision,0);
            }
            while(entrance_animation)
            {
                double y_audience1 = 390,y_audience2=305,h_audience = 30,g=1;
                string player1 =  "player1", player2 = "player2",confetti = "confetti";
                double x_head2 = x2 + 37,x_head1=x1+72, y_head2 = player2_y - h_head+5,y_head1 = player1_y - h_head+5;
                window_color(m_renderer,0,0,0);
                if(int(j) % 2 ==0 )
                {
                    y_audience1 -= 10;
                    y_audience2 -= 10;
                    h_audience += 10;
                }
                texture(m_renderer,0,0,"soccer stadium1.png",Width,Height);
                texture(m_renderer,x_audience,y_audience1,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 1*115,y_audience1,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 2*115,y_audience1,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 3*115,y_audience1,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 4*115,y_audience1,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 5*115,y_audience1,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 6*115,y_audience1,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 7*115,y_audience1,"audience.png",115,h_audience);
                texture(m_renderer,x_audience,y_audience2,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 1*115,y_audience2,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 2*115,y_audience2,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 3*115,y_audience2,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 4*115,y_audience2,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 5*115,y_audience2,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 6*115,y_audience2,"audience.png",115,h_audience);
                texture(m_renderer,x_audience + 7*115,y_audience2,"audience.png",115,h_audience);
                ad(m_renderer,ad_x1,ad_h,ad_w);
                texture(m_renderer,powerline1_x,powerline1_y,powerline1,powerline1_w,powerline1_h);
                texture(m_renderer,powerline2_x,powerline2_y,powerline2,powerline2_w,powerline2_h);


                ball = temp;
                stringstream a;
                a<<j;
                string str=a.str();
                ball+=str;
                if(walk_animation != 0)
                {
                    player1 += str;
                    player2+= str;
                }
                else if(walk_animation  == 0)
                {
                    player1 = "player11";
                    player2 = "player21";
                }
                ball+=".png";
                player1 += ".png";
                player2 += ".png";
                stringstream f;
                f << q;
                str = f.str();
                confetti += str;
                confetti += ".PNG";
                texture(m_renderer,ball_x,ball_y,ball,w_ball,h_ball);
                texture(m_renderer,x1,player1_y,player1,w_body,h_body);
                texture(m_renderer,x2,player2_y,player2,w_body,h_body);
                texture(m_renderer,x_head1,y_head1,player1_ch,h_head,w_head);
                texture(m_renderer,x_head2,y_head2,player2_ch,h_head,w_head);
                texture(m_renderer,0,0,confetti,Width,Height);
                j++;
                q++;
                if(j>4)
                    j=1;
                if(q > 16)
                    q = 1;
                ball_vy+=g;
                if((ball_y+ball_vy)<=560 && ball_y>=0)
                {
                    ball_y+=ball_vy;
                }
                else
                {
                    ball_y--;
                    ball_vy=-ball_vy;
                    ball_vy*=este;
                }
                x1 += walk_animation;
                x2 -= walk_animation;
                if(x1 >= player1_x || x2<=player2_x)
                    walk_animation = 0;
                e -> type = 0;
                SDL_PollEvent(e);
                //cout<<player1<<endl<<player2<<endl;
                if(e -> type == SDL_KEYDOWN)
                    entrance_animation = false;

                if(walk_animation == 0)
                    entrance_animation = false;
                text(m_renderer,timet_x,t_y,timet_w,timet_h,0,0,0,40,"0");//time
                text(m_renderer,x_name1,y_name,w_name,h_name,0,0,0,20,current_player1);//player 1 name on score board
                text(m_renderer,x_name2,y_name,w_name,h_name,0,0,0,20,current_player2);//player 2 name on score board
                text(m_renderer,x_score1,y_score,w_score,h_score,0,0,0,20,tostring(current_goal1));//score player 1
                text(m_renderer,x_score2,y_score,w_score,h_score,0,0,0,20,tostring(current_goal2));//score player 1
                SDL_Delay(20);
                SDL_RenderPresent(m_renderer);


            }
            string player1 =  "player11.png", player2 = "player21.png";
            ball_y=570,ball_vy=0,ball_vx=0,ball_ay=0;



            double game_time=0;
            double start=clock();
            double pausetime=0;
            double pausestart=0;
            double pauseend=0;

            while(!entrance_animation)
            {
                string thunder="thunder",rock="rock.png";
                double time = clock();
                int t=int((time-start-pausetime)/1000);
//                if(!pause && !goal1 && !goal2 )
//                {
//                    //double time=clock();
//
//                   // cout<<floor((time-start-pausetime)/1000)<<endl;
//
//                }

                shoot1=false;
                shoot2=false;
                double y_audience1 = 390,y_audience2=305,h_audience = 30,g=1;
                double x_head2 = player2_x + 37,x_head1=player1_x +72, y_head2 = player2_y - h_head+5,y_head1 = player1_y - h_head+5;
                window_color(m_renderer,0,0,0);
                texture(m_renderer,0,0,"soccer stadium1.png",Width,Height);
                ad(m_renderer,ad_x1,ad_h,ad_w);
                texture(m_renderer,player1_x,player1_y,player1,w_body,h_body);//render body 1
                texture(m_renderer,player2_x,player2_y,player2,w_body,h_body);//render body 2
                texture(m_renderer,x_head1,y_head1,player1_ch,w_head,h_head);//render head 1
                texture(m_renderer,x_head2,y_head2,player2_ch,w_head,h_head);//render head 2
                texture(m_renderer,ball_x,ball_y,ball,w_ball,h_ball);
                texture(m_renderer,powerline1_x,powerline1_y,powerline1,powerline1_w,powerline1_h);
                texture(m_renderer,powerline2_x,powerline2_y,powerline2,powerline2_w,powerline2_h);


                e->type = 0;
                SDL_PollEvent(e);
                SDL_GetMouseState(&x,&y);
                if(e-> type==SDL_MOUSEBUTTONDOWN)
                {
                    if(x > game_menu_x && x < game_menu_x+game_menu_w && y > game_menu_y && y < game_menu_y + game_menu_h)
                    {
                        pausestart=clock();
                        pause= true;
                    }
                }
                while(pause)
                {
                    window_color(m_renderer,0,0,0);
                    texture(m_renderer,0,0,"soccer stadium1.png",Width,Height);
                    ad(m_renderer,ad_x1,ad_h,ad_w);
                    texture(m_renderer,player1_x,player1_y,player1,w_body,h_body);//render body 1
                    texture(m_renderer,player2_x,player2_y,player2,w_body,h_body);//render body 2
                    texture(m_renderer,x_head1,y_head1,player1_ch,w_head,h_head);//render head 1
                    texture(m_renderer,x_head2,y_head2,player2_ch,w_head,h_head);//render head 2
                    texture(m_renderer,ball_x,ball_y,ball,w_ball,h_ball);
                    texture(m_renderer,game_menu_x,game_menu_y+game_menu_h+5,"return.png",game_menu_w,game_menu_h);
                    texture(m_renderer,game_menu_x,game_menu_y+2*(game_menu_h+5),"exit.png",game_menu_w,game_menu_h);
                    texture(m_renderer,game_menu_x,game_menu_y+3*(game_menu_h+5),"guide.png",game_menu_w,game_menu_h);
                texture(m_renderer,powerline1_x,powerline1_y,powerline1,powerline1_w,powerline1_h);
                texture(m_renderer,powerline2_x,powerline2_y,powerline2,powerline2_w,powerline2_h);




                    e->type = 0;
                    SDL_PollEvent(e);
                    SDL_GetMouseState(&x,&y);
                    if(e-> type==SDL_MOUSEBUTTONDOWN)
                    {
                        if(x > game_menu_x && x < game_menu_x+game_menu_w && y > game_menu_y && y < game_menu_y + game_menu_h)
                        {
                            pauseend=clock();
                            pausetime+=pauseend-pausestart;
                            pause= false;
                        }
                        else if(x > game_menu_x && x < game_menu_x+game_menu_w && y > game_menu_y+game_menu_h+5 && y <game_menu_h+ game_menu_y + game_menu_h+5)
                        {
                            start2=true;
                            main_game=false;
                            save_info(current_goal1,current_goal2,players,"",goals,losses,wins,n,current_player1,current_player2);
                            goal1 = false,goal2 = false, entrance_animation = true;


                            break;

                        }
                        else if(x > game_menu_x && x < game_menu_x+game_menu_w && y > game_menu_y+2*(game_menu_h+5) && y < game_menu_y + game_menu_h+2*(game_menu_h+5))
                        {
                            mainmenu = true;
                            main_game=false;
                            save_info(current_goal1,current_goal2,players,"",goals,losses,wins,n,current_player1,current_player2);
                            goal1 = false,goal2 = false, entrance_animation = true;
                            break;
                        }
                        else if(x > game_menu_x && x < game_menu_x+game_menu_w && y > game_menu_y+3*(game_menu_h+5) && y < game_menu_y + game_menu_h+3*(game_menu_h+5))
                        {
                            texture(m_renderer,350,150,"info.png",579,431);
                            bool guide=true;
                            while(guide)
                            {
                                ad(m_renderer,ad_x1,ad_h,ad_w);
                                e->type = 0;
                                SDL_PollEvent(e);
                                if(e -> type == SDL_KEYDOWN)
                                guide = false;

                                text(m_renderer,timet_x,t_y,timet_w,timet_h,0,0,0,40,tostring(t));//time
                                text(m_renderer,x_name1,y_name,w_name,h_name,0,0,0,20,current_player1);//player 1 name on score board
                                text(m_renderer,x_name2,y_name,w_name,h_name,0,0,0,20,current_player2);//player 2 name on score board
                text(m_renderer,x_score1,y_score,w_score,h_score,0,0,0,20,tostring(current_goal1));//score player 1
                text(m_renderer,x_score2,y_score,w_score,h_score,0,0,0,20,tostring(current_goal2));//score player 1
                                SDL_Delay(20);
                                SDL_RenderPresent(m_renderer);

                            }

                        }
                    }
                   text(m_renderer,timet_x,t_y,timet_w,timet_h,0,0,0,40,tostring(t));//time
                text(m_renderer,x_name1,y_name,w_name,h_name,0,0,0,20,current_player1);//player 1 name on score board
                text(m_renderer,x_name2,y_name,w_name,h_name,0,0,0,20,current_player2);//player 2 name on score board
                text(m_renderer,x_score1,y_score,w_score,h_score,0,0,0,20,tostring(current_goal1));//score player 1
                text(m_renderer,x_score2,y_score,w_score,h_score,0,0,0,20,tostring(current_goal2));//score player 1
                    SDL_Delay(20);
                    SDL_RenderPresent(m_renderer);
                }




                SDL_PollEvent(e);
                const Uint8* key = SDL_GetKeyboardState(NULL);
                if (key[SDL_SCANCODE_D])
                {
                    if(player1_x+walk<=967 && player1_x+walk>=149 &&(player1_x>player2_x || ((fabs(player1_x-player2_x)>=170+2*walk)) || (fabs(player1_y-player2_y)>=146)))
                        if(!rock_power || player1_x + 170 + walk <= x_rock)
                            player1_x+=walk;


                    if(!jump1)
                    {
                        player1="player1";
                        player1+=to_string(k1);
                        player1+=".png";
                        k1++;
                        if(k1>4)
                        {
                            k1=1;
                        }
                    }
                    else
                    {
                        player1="player11.png";
                    }
                }
                if (key[SDL_SCANCODE_A])
                {
                    if(player1_x-walk<=967 && player1_x-walk>=149  && (player1_x<player2_x || ((fabs(player1_x-player2_x)>=170+2*walk)) || (fabs(player1_y-player2_y)>=146)))
                        player1_x-=walk;
                    if(!jump1)
                    {
                        player1="player1";
                        if(k1-1>=1 && k1-1<=4)
                        {
                            k1--;
                        }
                        else
                        {
                            k1=4;
                        }
                        player1+=to_string(k1);
                        player1+=".png";
                    }
                    else
                    {
                        player1="player11.png";
                    }
                }
                if (key[SDL_SCANCODE_W])
                {
                    shoot1=true;
                }
                if (key[SDL_SCANCODE_S])
                {
                    jump1=true;


                }
                if(key[SDL_SCANCODE_L])
                {
                    if(player2_x+walk<=967 && player2_x+walk>=149 && (player1_x<player2_x || ((fabs(player1_x-player2_x)>=170+2*walk)) || (fabs(player1_y-player2_y)>=146)) && (!thunder_power))
                        player2_x+=walk;

                    if(!jump2)
                    {
                        player2="player2";
                        player2+=to_string(k2);
                        player2+=".png";
                        k2++;
                        if(k2>4)
                        {
                            k2=1;
                        }
                    }
                    else
                    {
                        player2="player21.png";
                    }
                }
                if(key[SDL_SCANCODE_J])
                {
                    if(player2_x-walk<=967 && player2_x-walk>=149  && (player1_x>player2_x || ((fabs(player1_x-player2_x)>=170+2*walk)) || (fabs(player1_y-player2_y)>=146)) && (!thunder_power))
                        player2_x-=walk;
                    if(!jump2)
                    {
                        player2="player2";
                        if(k2-1>=1 && k2-1<=4)
                        {
                            k2--;
                        }
                        else
                        {
                            k2=4;
                        }
                        player2+=to_string(k2);
                        player2+=".png";
                    }
                    else
                    {
                        player2="player21.png";
                    }
                }
                if (key[SDL_SCANCODE_K] &&  !thunder_power)
                {
                    jump2=true;
                }
                if (key[SDL_SCANCODE_I] && !thunder_power)
                {
                    shoot2=true;

                }
                if (key[SDL_SCANCODE_E] && powerline1_full)
                {

                    thunder_power = true;
                    t_thunder = t;
                    powerline1_full=false;
                    extra_power1 = 0;
                    pu1 = t;

                }
                if (key[SDL_SCANCODE_U] && powerline2_full )
                {

                    rock_power = true;
                    t_rock = t;
                    powerline2_full=false;
                    extra_power2 = 0;
                    pu2 = t;

                }

                if(jump1)
                {
                    player1_y+=jump_1;
                    jump_1+=g;
                    if(player1_y>=474)
                    {
                        jump_1=-20;
                        player1_y=474;
                        jump1=false;
                    }
                }
                if(jump2)
                {
                    player2_y+=jump_2;
                    jump_2+=g;
                    if(player2_y>=474)
                    {
                        jump_2=-20;
                        player2_y=474;
                        jump2=false;
                    }
                }
                if(thunder_power){
                    if(t - t_thunder >= 5){
                        thunder_power=false;
                        c=1;
                    }
                    c++;
                    thunder += to_string(c);
                    thunder += ".png";
                    if(c > 4)
                        c=1;
                    texture(m_renderer,player2_x,player2_y-200,thunder,170,346);
                }
                if(rock_power){
                    if(t-t_rock >= 5){
                        rock_power = false;
                    }
                    texture(m_renderer,x_rock,y_rock,rock,w_rock,h_rock);
                }


                SDL_PollEvent(e);
                if(e-> type==SDL_KEYUP)
                {
                    running=false;
                    player1="player11.png";
                    player2="player21.png";
                }

                ball = temp;
                stringstream a;
                a<<j;
                string str=a.str();
                ball+=str;
                ball+=".png";
                j++;
                if(j>4)
                    j=1;

                if(!powerline1_full){
                    p1=(int((t-pu1)/5))% 6 + 1 + extra_power1;
                   if(p1 >= 6){
                        p1=6;
                        powerline1_full = true;
                   }
                    powerline1="power1";
                    powerline1 += to_string(p1);
                    powerline1 += ".png";
                }
                if(!powerline2_full){
                   p2=(int((t-pu2)/5))% 6 + 1 + extra_power2;
                   if(p2 >= 6){
                        p2=6;
                        powerline2_full = true;
                   }
                    powerline2="power2";
                    powerline2 += to_string(p2);
                    powerline2 += ".png";
                }








                if(shoot1 &&(ball_x + h_ball/2>= player1_x + 142) && (ball_x + h_ball/2 <= player1_x + 170) && (fabs(ball_y  + h_ball - player1_y - 133) <= 5))
                {
                    //roppa1
                    ball_ay=2;
                    ball_vy =-20 ;
                    ball_vx = 20;
                }
                else if(shoot1 &&(fabs(ball_x - player1_x - 170) <= 10)  && (ball_y + h_ball / 2 >= player1_y + 133) && (ball_y + h_ball / 2 <= player1_y + 146))
                {
                    // ball_ax = 0.1;
                    //jelopa1
                    ball_ay=2;
                    ball_vy = -4;
                    ball_vx = 20;
                }
                else if(shoot1 &&(ball_x + h_ball/2>= player1_x + 143) && (ball_x + h_ball/2 <= player1_x + 170) && (fabs(ball_y - player1_y  - 146) <= 5))
                {
                    //ball_ax = 0.1;
                    //zrpa 1
                    ball_ay=2;
                    ball_vx = 20;
                    ball_vy = 20;
                }
                else if(shoot2 &&(ball_x + h_ball/2 >= player2_x) && (ball_x + h_ball/2 <= player2_x + 27) && (fabs(ball_y + h_ball - player2_y - 134) <= 5))
                {
                    // ball_ax = -0.1;
                    //roopa2
                    ball_ay=2;
                    ball_vx = -20;
                    ball_vy = -20;
                }
                else if(shoot2 &&(fabs(ball_x + h_ball - player2_x)<=10) && (ball_y + h_ball/2 >= player2_y + 134) && (ball_y + h_ball/2 <= player2_y + 146))
                {
                    //jelopa 2
                    ball_ay=2;
                    ball_vx = -20;
                    ball_vy = -4;
                }
                else if(shoot2 &&(ball_x + h_ball/2 >= player2_x) && (ball_x + h_ball/2 <= player2_x + 27) && (fabs(ball_y - player2_y - 146) <= 5))
                {
                    //  ball_ax = -0.1;
                    //zirpa 2
                    ball_ay=2;
                    ball_vx = -20;
                    ball_vy = 20;
                }
                if((ball_x + h_ball>= x_goal_right )&& (ball_y <= y_goal_right) )
                {
                    //goal right
                    ball_vx =- ball_vx;
                }
                else if((ball_x <= x_goal_left + w_goal) &&( ball_y <= y_goal_left ))
                {
                    //goal left
                    ball_x++;
                    ball_vx =- ball_vx;
                }
                if((ball_x + h_ball + ball_vx >= x_rock && ball_x <= x_rock) && rock_power)
                {
                    //rock power
                    ball_x = x_rock - h_ball - 1;
                    ball_vx =- ball_vx;
                    ball_vy =- ball_vy;

                }
                if(ball_x>=x_goal_left+135 && ball_y>=y_goal_left && (ball_x <=x_goal_left + 175) )
                {
                    if(ball_x+ball_vx<=x_goal_left+135)
                        ball_vx = 0;
                    goal2=true;
                    extra_power2++;
                }
                else if(ball_x >=x_goal_right  && ball_y>=y_goal_right && ball_x+h_ball<=x_goal_right+75 && !rock_power)
                {
                    if(ball_x+h_ball+ball_vx>=x_goal_right+75)
                        ball_vx = 0;

                    goal1=true;
                    extra_power1++;
                }
                if(ball_y+ball_vy+h_ball>=player1_y && ball_y<=player1_y && player1_x<=ball_x && ball_x<=player1_x+143)
                {
                    //balaye b 1
                    ball_y=player1_y-h_ball - 1;
                    ball_vx=-ball_vx;
                    ball_vy=-ball_vy;
                    ball_vy *= zarib;
                    ball_vx *= zarib;

                }
                else if(y_head1<=ball_y && ball_y<=y_head1+h_head && ball_x<=x_head1 && ball_x+h_ball+ball_vx>=x_head1)
                {
                    //posht sar 1
                    ball_x = x_head1 -h_ball - 1;
                    ball_vx=-ball_vx;
                    ball_vy=-ball_vy;
                }
                else if(ball_x+ball_vx<=player1_x + 143 && player1_x + 85<=ball_x   && ball_y >=y_head1 && ball_y + 20 <=player1_y+134)
                {
                    //jelo 1
                    ball_x = player1_x + 144;
                    ball_vx= -ball_vx;
                    ball_vy= -ball_vy;
                    ball_vy *= zarib;
                    ball_vx *= zarib;
                }

                else if(x_head1<=ball_x && ball_x<=x_head1+h_head && ball_y<=y_head1 && ball_y+h_ball+ball_vy>=y_head1 )
                {
                    //balaye sar 1
                    ball_y=y_head1 - h_ball - 1;
                    ball_vx=-ball_vx;
                    ball_vy=-ball_vy;

                }
                else  if(ball_x+ball_vx+h_ball>=player1_x && player1_x>=ball_x  && ball_y>=player1_y && ball_y<=player1_y+134)
                {
                    //posht 1
                    ball_x = player1_x -h_ball- 1;
                    ball_vx=-ball_vx;
                    ball_vy=-ball_vy;
                    ball_vy *= zarib;
                    ball_vx *= zarib;
                }
                else  if(ball_y>=player1_y && ball_y+ball_vy<=player1_y+134 && player1_x<=ball_x && ball_x<=player1_x+143)
                {
                    //zir 1
                    ball_y = player1_y + 135;
                    ball_vy=-ball_vy;
                    ball_vx=-ball_vx;
                    ball_vy *= zarib;
                    ball_vx *= zarib;
                }

                if(ball_x <= player2_x && ball_x + ball_vx + h_ball >= player2_x + 30 && ball_y >= y_head2 && ball_y <= player2_y + 134)
                {
                    //jelo 2
                    ball_x = player2_x + 29 - h_ball;
                    ball_vx=-ball_vx;
                    ball_vy=-ball_vy;
                    ball_vy *= zarib;
                    ball_vx *= zarib;

                }
                else if(ball_x >= x_head2 + h_head && ball_x + ball_vx <= x_head2 + h_head && y_head2 <= ball_y && ball_y <= y_head2 + h_head)
                {
                    //posht sar 2
                    ball_x=x_head2+h_head +1;
                    ball_vx=-ball_vx;
                    ball_vy=-ball_vy;


                }
                else if(ball_y <= y_head2 && ball_y + ball_vy + h_ball >= y_head2 && x_head2 <= ball_x + h_ball && ball_x <= x_head2 + h_head)
                {
                    //balaye sar 2
                    ball_y=y_head2 - h_ball - 1;
                    ball_vx=-ball_vx;
                    ball_vy=-ball_vy;

                }
                else if(ball_x + h_ball >= player2_x+170 && ball_x + ball_vx <= player2_x + 170 && ball_y >= player2_y && ball_y <= player2_y + 134)
                {
                    //posht 2
                    ball_x = player2_x + 171;
                    ball_vx=-ball_vx;
                    ball_vy=-ball_vy;
                    ball_vy *= zarib;
                    ball_vx *= zarib;
                }
                else if(ball_y <= player2_y && ball_y + ball_vy + h_ball >= player2_y && player2_x +30 <= ball_x && ball_x <= player2_x + 170)
                {
                    //balaye b 2
                    ball_y=player2_y - h_ball - 1;
                    ball_vx=-ball_vx;
                    ball_vy=-ball_vy;
                    ball_vy *= zarib;
                    ball_vx *= zarib;
                }
                else if(ball_y >= player2_y && ball_y + ball_vy <= player2_y + 134 && player2_x + 30 <= ball_x && ball_x <= player2_x +170)
                {
                    //zir 2
                    ball_y=player2_y + 135;
                    ball_vx=-ball_vx;
                    ball_vy=-ball_vy;
                    ball_vy *= zarib;
                    ball_vx *= zarib;
                }


                if(ball_y+h_ball+ball_vy<=610)
                {
                    ball_y+=ball_vy;
                }

                else if(ball_y+h_ball+ball_vy>=610)
                {

                    ball_y=610-h_ball-ball_vy;
                    ball_vy=-ball_vy;
                    ball_vy*=zarib;
                    ball_vx*=zarib;

                }

                ball_y += ball_vy;
                ball_vy += ball_ay;
                ball_x += ball_vx;




                if(goal1 || goal2)
                {
                    ball_y=300;
                    ball_x=Width/2-20;
                    g = 4,q=1;
                    ball_vy=0;
                    ball_vx=0;
                    player1_x=350,player1_y=474,player2_x=755,player2_y=474;
                    pausestart=clock();
                    Mix_PlayChannel(-1,collision,0);
                }
               text(m_renderer,timet_x,t_y,timet_w,timet_h,0,0,0,40,tostring(t));//time
                text(m_renderer,x_name1,y_name,w_name,h_name,0,0,0,20,current_player1);//player 1 name on score board
                text(m_renderer,x_name2,y_name,w_name,h_name,0,0,0,20,current_player2);//player 2 name on score board
                text(m_renderer,x_score1,y_score,w_score,h_score,0,0,0,20,tostring(current_goal1));//score player 1
                text(m_renderer,x_score2,y_score,w_score,h_score,0,0,0,20,tostring(current_goal2));//score player 1

                while (goal1)
                {
                    double y_audience1 = 390,y_audience2=305,h_audience = 30, x_head2 = player2_x + 37,x_head1=player1_x +72,y_head2 = player2_y - h_head+5,y_head1 = player1_y - h_head+5;
                    string player1 =  "player11.png", player2 = "player21.png",confetti = "confetti";
                    window_color(m_renderer,0,0,0);
                    if(int(j) % 2 ==0 )
                    {
                        y_audience1 -= 10;
                        y_audience2 -= 10;
                        h_audience += 10;
                    }
                    texture(m_renderer,0,0,"soccer stadium1.png",Width,Height);
                    texture(m_renderer,x_audience,y_audience1,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 1*115,y_audience1,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 2*115,y_audience1,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 3*115,y_audience1,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 4*115,390,"audience.png",115,30);
                    texture(m_renderer,x_audience + 5*115,390,"audience.png",115,30);
                    texture(m_renderer,x_audience + 6*115,390,"audience.png",115,30);
                    texture(m_renderer,x_audience + 7*115,390,"audience.png",115,30);
                    texture(m_renderer,x_audience,y_audience2,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 1*115,y_audience2,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 2*115,y_audience2,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 3*115,y_audience2,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 4*115,305,"audience.png",115,30);
                    texture(m_renderer,x_audience + 5*115,305,"audience.png",115,30);
                    texture(m_renderer,x_audience + 6*115,305,"audience.png",115,30);
                    texture(m_renderer,x_audience + 7*115,305,"audience.png",115,30);
                    ad(m_renderer,ad_x1,ad_h,ad_w);
                    texture(m_renderer,powerline1_x,powerline1_y,powerline1,powerline1_w,powerline1_h);
                    texture(m_renderer,powerline2_x,powerline2_y,powerline2,powerline2_w,powerline2_h);

                    ball = temp;
                    stringstream a;
                    a<<j;
                    string str=a.str();
                    ball+=str;
                    ball+=".png";
                    texture(m_renderer,ball_x,ball_y,ball,w_ball,h_ball);
                    stringstream f;
                    f << q;
                    str = f.str();
                    confetti += str;
                    confetti += ".PNG";
                    texture(m_renderer,player1_x,player1_y,player1,w_body,h_body);
                    texture(m_renderer,player2_x,player2_y,player2,w_body,h_body);
                    texture(m_renderer,x_head1,y_head1,player1_ch,h_head,w_head);
                    texture(m_renderer,x_head2,y_head2,player2_ch,h_head,w_head);
                    texture(m_renderer,0,0,confetti,Width,Height);
                    j++;
                    q++;
                    if(j>4)
                        j=1;
                    if(q > 16)
                        q = 1;
                    ball_vy+=g;
                    if((ball_y+ball_vy)<=570 && ball_y>=0)
                    {
                        ball_y+=ball_vy;
                    }
                    else
                    {
                        ball_y--;
                        ball_vy=-ball_vy;
                        ball_vy*=este;
                    }

                    e -> type = 0;
                    SDL_PollEvent(e);
                    if(e -> type == SDL_KEYDOWN)
                    {
                        current_goal1++;
                        goal1 = false;
                        pauseend = clock();
                        pausetime += pauseend - pausestart;
                        string player1 =  "player11.png", player2 = "player21.png";
                        ball_y=570,ball_vy=0,ball_vx=0,ball_ay=0;
                        q=1;
                    }
                text(m_renderer,timet_x,t_y,timet_w,timet_h,0,0,0,40,tostring(t));//time
                text(m_renderer,x_name1,y_name,w_name,h_name,0,0,0,20,current_player1);//player 1 name on score board
                text(m_renderer,x_name2,y_name,w_name,h_name,0,0,0,20,current_player2);//player 2 name on score board
                text(m_renderer,x_score1,y_score,w_score,h_score,0,0,0,20,tostring(current_goal1));//score player 1
                text(m_renderer,x_score2,y_score,w_score,h_score,0,0,0,20,tostring(current_goal2));//score player 1
                    SDL_Delay(20);
                    SDL_RenderPresent(m_renderer);
                }


                while (goal2)
                {
                    double y_audience1 = 390,y_audience2=305,h_audience = 30, x_head2 = player2_x + 37,x_head1=player1_x +72, y_head2 = player2_y - h_head+5,y_head1 = player1_y - h_head+5;
                    string player1 =  "player11.png", player2 = "player21.png",confetti = "confetti";
                    window_color(m_renderer,0,0,0);
                    if(int(j) % 2 ==0 )
                    {
                        y_audience1 -= 10;
                        y_audience2 -= 10;
                        h_audience += 10;
                    }
                    texture(m_renderer,0,0,"soccer stadium1.png",Width,Height);
                    texture(m_renderer,x_audience + 4*115,y_audience1,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 5*115,y_audience1,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 6*115,y_audience1,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 7*115,y_audience1,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience,390,"audience.png",115,30);
                    texture(m_renderer,x_audience + 1*115,390,"audience.png",115,30);
                    texture(m_renderer,x_audience + 2*115,390,"audience.png",115,30);
                    texture(m_renderer,x_audience + 3*115,390,"audience.png",115,30);
                    texture(m_renderer,x_audience+ 4*115,y_audience2,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 5*115,y_audience2,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 6*115,y_audience2,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience + 7*115,y_audience2,"audience.png",115,h_audience);
                    texture(m_renderer,x_audience,305,"audience.png",115,30);
                    texture(m_renderer,x_audience + 1*115,305,"audience.png",115,30);
                    texture(m_renderer,x_audience + 2*115,305,"audience.png",115,30);
                    texture(m_renderer,x_audience + 3*115,305,"audience.png",115,30);
                    texture(m_renderer,powerline1_x,powerline1_y,powerline1,powerline1_w,powerline1_h);
                    texture(m_renderer,powerline2_x,powerline2_y,powerline2,powerline2_w,powerline2_h);


                    ball = temp;
                    stringstream a;
                    a<<j;
                    string str=a.str();
                    ball+=str;
                    ball+=".png";
                    texture(m_renderer,ball_x,ball_y,ball,w_ball,h_ball);
                    stringstream f;
                    f << q;
                    str = f.str();
                    confetti += str;
                    confetti += ".PNG";
                    texture(m_renderer,player1_x,player1_y,player1,w_body,h_body);
                    texture(m_renderer,player2_x,player2_y,player2,w_body,h_body);
                    texture(m_renderer,x_head1,y_head1,player1_ch,h_head,w_head);
                    texture(m_renderer,x_head2,y_head2,player2_ch,h_head,w_head);
                    texture(m_renderer,0,0,confetti,Width,Height);
                    ad(m_renderer,ad_x1,ad_h,ad_w);
                    j++;
                    q++;
                    if(j>4)
                        j=1;
                    if(q > 16)
                        q = 1;
                    ball_vy+=g;
                    if((ball_y+ball_vy)<=570 && ball_y>=0)
                    {
                        ball_y+=ball_vy;
                    }
                    else
                    {
                        ball_y--;
                        ball_vy=-ball_vy;
                        ball_vy*=este;
                    }
                    e->type = 0;
                    SDL_PollEvent(e);
                    if(e -> type == SDL_KEYDOWN)
                    {
                        current_goal2++;
                        goal2 = false;
                        pauseend=clock();
                        pausetime+=pauseend-pausestart;
                        string player1 =  "player11.png", player2 = "player21.png";
                        ball_y=570,ball_vy=0,ball_vx=0,ball_ay=0;
                        q=1;
                    }
                   text(m_renderer,timet_x,t_y,timet_w,timet_h,0,0,0,40,tostring(t));//time
                text(m_renderer,x_name1,y_name,w_name,h_name,0,0,0,20,current_player1);//player 1 name on score board
                text(m_renderer,x_name2,y_name,w_name,h_name,0,0,0,20,current_player2);//player 2 name on score board
                text(m_renderer,x_score1,y_score,w_score,h_score,0,0,0,20,tostring(current_goal1));//score player 1
                text(m_renderer,x_score2,y_score,w_score,h_score,0,0,0,20,tostring(current_goal2));//score player 1
                    SDL_Delay(20);
                    SDL_RenderPresent(m_renderer);
                }







                if(ending_type=="5goal" && current_goal1==4 && current_goal2==4) //Tie
                {
                    string winner = "";
                    Mix_PlayChannel(-1,collision,0);
                    while(true)
                    {
                        double y_audience1 = 390,y_audience2=305,h_audience = 30, x_head2 = player2_x + 37,x_head1=player1_x +72, y_head2 = player2_y - h_head+5,y_head1 = player1_y - h_head+5;
                        string player1 =  "player11.png", player2 = "player21.png",confetti = "confetti";
                        window_color(m_renderer,0,0,0);
                        texture(m_renderer,0,0,"soccer stadium1.png",Width,Height);

                        ball = temp;
                        ball +="1.png";
                        texture(m_renderer,640,570,ball,w_ball,h_ball);
                        texture(m_renderer,player1_x,player1_y,player1,w_body,h_body);
                        texture(m_renderer,player2_x,player2_y,player2,w_body,h_body);
                        texture(m_renderer,x_head1,y_head1,player1_ch,h_head,w_head);
                        texture(m_renderer,x_head2,y_head2,player2_ch,h_head,w_head);
                        texture(m_renderer,445,360,"tie.PNG",400,160);//Tie sign
                        ad(m_renderer,ad_x1,ad_h,ad_w);
                        texture(m_renderer,powerline1_x,powerline1_y,powerline1,powerline1_w,powerline1_h);
                        texture(m_renderer,powerline2_x,powerline2_y,powerline2,powerline2_w,powerline2_h);



                        e->type = 0;
                        SDL_PollEvent(e);
                        if(e -> type == SDL_KEYDOWN)
                        {
                            save_info(current_goal1,current_goal2,players,winner,goals,losses,wins,n,current_player1,current_player2);
                            mainmenu = true;
                            main_game=false;
                            goal1 = false,goal2 = false, entrance_animation = true;
                            break;
                        }
                        text(m_renderer,timet_x,t_y,timet_w,timet_h,0,0,0,40,tostring(t));//time
                text(m_renderer,x_name1,y_name,w_name,h_name,0,0,0,20,current_player1);//player 1 name on score board
                text(m_renderer,x_name2,y_name,w_name,h_name,0,0,0,20,current_player2);//player 2 name on score board
                text(m_renderer,x_score1,y_score,w_score,h_score,0,0,0,20,tostring(current_goal1));//score player 1
                text(m_renderer,x_score2,y_score,w_score,h_score,0,0,0,20,tostring(current_goal2));//score player 1
                        SDL_Delay(20);
                        SDL_RenderPresent(m_renderer);
                    }

                }
                else if(ending_type=="5goal" && current_goal1==5 ) //player1 wins
                {
                    string winner = current_player1;
                    Mix_PlayChannel(-1,collision,0);
                    while(true)
                    {
                        double y_audience1 = 390,y_audience2=305,h_audience = 30, x_head2 = player2_x + 37,x_head1=player1_x +72,y_head2 = player2_y - h_head+5,y_head1 = player1_y - h_head+5;
                        string player1 =  "player11.png", player2 = "player21.png",confetti = "confetti";
                        window_color(m_renderer,0,0,0);
                        if(int(q) % 2 ==0 )
                        {
                            y_audience1 -= 10;
                            y_audience2 -= 10;
                            h_audience += 10;
                        }
                        texture(m_renderer,0,0,"soccer stadium1.png",Width,Height);
                        texture(m_renderer,x_audience,y_audience1,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 1*115,y_audience1,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 2*115,y_audience1,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 3*115,y_audience1,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 4*115,390,"audience.png",115,30);
                        texture(m_renderer,x_audience + 5*115,390,"audience.png",115,30);
                        texture(m_renderer,x_audience + 6*115,390,"audience.png",115,30);
                        texture(m_renderer,x_audience + 7*115,390,"audience.png",115,30);
                        texture(m_renderer,x_audience,y_audience2,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 1*115,y_audience2,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 2*115,y_audience2,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 3*115,y_audience2,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 4*115,305,"audience.png",115,30);
                        texture(m_renderer,x_audience + 5*115,305,"audience.png",115,30);
                        texture(m_renderer,x_audience + 6*115,305,"audience.png",115,30);
                        texture(m_renderer,x_audience + 7*115,305,"audience.png",115,30);
                        ad(m_renderer,ad_x1,ad_h,ad_w);
                        texture(m_renderer,powerline1_x,powerline1_y,powerline1,powerline1_w,powerline1_h);
                        texture(m_renderer,powerline2_x,powerline2_y,powerline2,powerline2_w,powerline2_h);


                        ball = temp;
                        ball+="1.png";
                        texture(m_renderer,ball_x,ball_y,ball,w_ball,h_ball);
                        stringstream f;
                        f << q;
                        str = f.str();
                        confetti += str;
                        confetti += ".PNG";
                        texture(m_renderer,player1_x,player1_y,player1,w_body,h_body);
                        texture(m_renderer,player2_x,player2_y,player2,w_body,h_body);
                        texture(m_renderer,x_head1,y_head1,player1_ch,h_head,w_head);
                        texture(m_renderer,x_head2,y_head2,player2_ch,h_head,w_head);
                        texture(m_renderer,0,0,confetti,Width,Height);
                        texture(m_renderer,460,160,"winnercup.png",360,390);//CUP sign
                        q++;

                        if(q > 16)
                            q = 1;

                        e -> type = 0;
                        SDL_PollEvent(e);
                        if(e -> type == SDL_KEYDOWN)
                        {
                            save_info(current_goal1,current_goal2,players,winner,goals,losses,wins,n,current_player1,current_player2);
                            mainmenu = true;
                            main_game=false;
                            goal1 = false,goal2 = false, entrance_animation = true;
                            break;
                        }

                       text(m_renderer,timet_x,t_y,timet_w,timet_h,0,0,0,40,tostring(t));//time
                text(m_renderer,x_name1,y_name,w_name,h_name,0,0,0,20,current_player1);//player 1 name on score board
                text(m_renderer,x_name2,y_name,w_name,h_name,0,0,0,20,current_player2);//player 2 name on score board
                text(m_renderer,x_score1,y_score,w_score,h_score,0,0,0,20,tostring(current_goal1));//score player 1
                text(m_renderer,x_score2,y_score,w_score,h_score,0,0,0,20,tostring(current_goal2));//score player 1
                text(m_renderer,570,410,140,35,0,0,0,40,winner);
                        SDL_Delay(20);
                        SDL_RenderPresent(m_renderer);
                    }

                }
                else if(ending_type=="5goal" && current_goal2>=5 ) //player2 wins
                {
                    string winner = current_player2;
                    Mix_PlayChannel(-1,collision,0);
                    while(true)
                    {
                        double y_audience1 = 390,y_audience2=305,h_audience = 30, x_head2 = player2_x + 37,x_head1=player1_x +72, y_head2 = player2_y - h_head+5,y_head1 = player1_y - h_head+5;
                        string player1 =  "player11.png", player2 = "player21.png",confetti = "confetti";
                        window_color(m_renderer,0,0,0);
                        if(int(q) % 2 ==0 )
                        {
                            y_audience1 -= 10;
                            y_audience2 -= 10;
                            h_audience += 10;
                        }
                        texture(m_renderer,0,0,"soccer stadium1.png",Width,Height);
                        texture(m_renderer,x_audience + 4*115,y_audience1,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 5*115,y_audience1,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 6*115,y_audience1,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 7*115,y_audience1,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience,390,"audience.png",115,30);
                        texture(m_renderer,x_audience + 1*115,390,"audience.png",115,30);
                        texture(m_renderer,x_audience + 2*115,390,"audience.png",115,30);
                        texture(m_renderer,x_audience + 3*115,390,"audience.png",115,30);
                        texture(m_renderer,x_audience+ 4*115,y_audience2,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 5*115,y_audience2,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 6*115,y_audience2,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience + 7*115,y_audience2,"audience.png",115,h_audience);
                        texture(m_renderer,x_audience,305,"audience.png",115,30);
                        texture(m_renderer,x_audience + 1*115,305,"audience.png",115,30);
                        texture(m_renderer,x_audience + 2*115,305,"audience.png",115,30);
                        texture(m_renderer,x_audience + 3*115,305,"audience.png",115,30);
                        texture(m_renderer,powerline1_x,powerline1_y,powerline1,powerline1_w,powerline1_h);
                        texture(m_renderer,powerline2_x,powerline2_y,powerline2,powerline2_w,powerline2_h);



                        ball = temp;
                        ball+="1.png";
                        texture(m_renderer,ball_x,ball_y,ball,w_ball,h_ball);
                        stringstream f;
                        f << q;
                        str = f.str();
                        confetti += str;
                        confetti += ".PNG";
                        texture(m_renderer,player1_x,player1_y,player1,w_body,h_body);
                        texture(m_renderer,player2_x,player2_y,player2,w_body,h_body);
                        texture(m_renderer,x_head1,y_head1,player1_ch,h_head,w_head);
                        texture(m_renderer,x_head2,y_head2,player2_ch,h_head,w_head);
                        texture(m_renderer,0,0,confetti,Width,Height);
                        ad(m_renderer,ad_x1,ad_h,ad_w);
                        texture(m_renderer,460,160,"winnercup.png",360,390);//CUP sign
                        q++;
                        if(q > 16)
                            q = 1;

                        e->type = 0;
                        SDL_PollEvent(e);
                        if(e -> type == SDL_KEYDOWN)
                        {
                            save_info(current_goal1,current_goal2,players,winner,goals,losses,wins,n,current_player1,current_player2);
                           // cout<<"after save... \n";
                            mainmenu = true;
                            main_game=false;
                            goal1 = false,goal2 = false, entrance_animation = true;
                            break;
                        }
                       text(m_renderer,timet_x,t_y,timet_w,timet_h,0,0,0,40,tostring(t));//time
                text(m_renderer,x_name1,y_name,w_name,h_name,0,0,0,20,current_player1);//player 1 name on score board
                text(m_renderer,x_name2,y_name,w_name,h_name,0,0,0,20,current_player2);//player 2 name on score board
                text(m_renderer,x_score1,y_score,w_score,h_score,0,0,0,20,tostring(current_goal1));//score player 1
                text(m_renderer,x_score2,y_score,w_score,h_score,0,0,0,20,tostring(current_goal2));//score player 1
                        text(m_renderer,570,410,140,35,0,0,0,40,winner);
                        SDL_Delay(20);
                        SDL_RenderPresent(m_renderer);
                       // cout<<"goal 2 end \n";
                    }
                }
                else if(ending_type=="90s"  && floor(time - start - pausetime)/1000>=90)
                {
                    if(current_goal1 == current_goal2)//Tie
                    {
                        string winner = "";
                        Mix_PlayChannel(-1,collision,0);
                        while(true)
                        {
                            double y_audience1 = 390,y_audience2=305,h_audience = 30, x_head2 = player2_x + 37,x_head1=player1_x +72, y_head2 = player2_y - h_head+5,y_head1 = player1_y - h_head+5;
                            string player1 =  "player11.png", player2 = "player21.png",confetti = "confetti";
                            window_color(m_renderer,0,0,0);
                            texture(m_renderer,0,0,"soccer stadium1.png",Width,Height);


                            ball = temp;
                            ball +="1.png";
                            texture(m_renderer,640,570,ball,w_ball,h_ball);
                            texture(m_renderer,player1_x,player1_y,player1,w_body,h_body);
                            texture(m_renderer,player2_x,player2_y,player2,w_body,h_body);
                            texture(m_renderer,x_head1,y_head1,player1_ch,h_head,w_head);
                            texture(m_renderer,x_head2,y_head2,player2_ch,h_head,w_head);
                            texture(m_renderer,445,360,"tie.PNG",400,160);//Tie sign
                            ad(m_renderer,ad_x1,ad_h,ad_w);

                            e->type = 0;
                            SDL_PollEvent(e);
                            if(e -> type == SDL_KEYDOWN)
                            {
                                save_info(current_goal1,current_goal2,players,winner,goals,losses,wins,n,current_player1,current_player2);
                                mainmenu = true;
                                main_game=false;
                                goal1 = false,goal2 = false, entrance_animation = true;
                                break;
                            }
                           text(m_renderer,timet_x,t_y,timet_w,timet_h,0,0,0,40,tostring(t));//time
                        text(m_renderer,x_name1,y_name,w_name,h_name,0,0,0,20,current_player1);//player 1 name on score board
                        text(m_renderer,x_name2,y_name,w_name,h_name,0,0,0,20,current_player2);//player 2 name on score board
                        text(m_renderer,x_score1,y_score,w_score,h_score,0,0,0,20,tostring(current_goal1));//score player 1
                        text(m_renderer,x_score2,y_score,w_score,h_score,0,0,0,20,tostring(current_goal2));//score player 1
                            SDL_Delay(20);
                            SDL_RenderPresent(m_renderer);
                        }

                    }
                    else if(current_goal1 >= current_goal2)//player1 wins
                    {
                        string winner = current_player1;
                        Mix_PlayChannel(-1,collision,0);
                        while(true)
                        {
                            double y_audience1 = 390,y_audience2=305,h_audience = 30, x_head2 = player2_x + 37,x_head1=player1_x +72,y_head2 = player2_y - h_head+5,y_head1 = player1_y - h_head+5;
                            string player1 =  "player11.png", player2 = "player21.png",confetti = "confetti";
                            window_color(m_renderer,0,0,0);
                            if(int(q) % 2 ==0 )
                            {
                                y_audience1 -= 10;
                                y_audience2 -= 10;
                                h_audience += 10;
                            }
                            texture(m_renderer,0,0,"soccer stadium1.png",Width,Height);
                            texture(m_renderer,x_audience,y_audience1,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 1*115,y_audience1,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 2*115,y_audience1,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 3*115,y_audience1,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 4*115,390,"audience.png",115,30);
                            texture(m_renderer,x_audience + 5*115,390,"audience.png",115,30);
                            texture(m_renderer,x_audience + 6*115,390,"audience.png",115,30);
                            texture(m_renderer,x_audience + 7*115,390,"audience.png",115,30);
                            texture(m_renderer,x_audience,y_audience2,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 1*115,y_audience2,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 2*115,y_audience2,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 3*115,y_audience2,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 4*115,305,"audience.png",115,30);
                            texture(m_renderer,x_audience + 5*115,305,"audience.png",115,30);
                            texture(m_renderer,x_audience + 6*115,305,"audience.png",115,30);
                            texture(m_renderer,x_audience + 7*115,305,"audience.png",115,30);
                            ad(m_renderer,ad_x1,ad_h,ad_w);
                            texture(m_renderer,powerline1_x,powerline1_y,powerline1,powerline1_w,powerline1_h);
                            texture(m_renderer,powerline2_x,powerline2_y,powerline2,powerline2_w,powerline2_h);



                            ball = temp;
                            ball+="1.png";
                            texture(m_renderer,ball_x,ball_y,ball,w_ball,h_ball);
                            stringstream f;
                            f << q;
                            str = f.str();
                            confetti += str;
                            confetti += ".PNG";
                            texture(m_renderer,player1_x,player1_y,player1,w_body,h_body);
                            texture(m_renderer,player2_x,player2_y,player2,w_body,h_body);
                            texture(m_renderer,x_head1,y_head1,player1_ch,h_head,w_head);
                            texture(m_renderer,x_head2,y_head2,player2_ch,h_head,w_head);
                            texture(m_renderer,0,0,confetti,Width,Height);
                            texture(m_renderer,460,160,"winnercup.png",360,390);//CUP sign
                            q++;

                            if(q > 16)
                                q = 1;

                            e -> type = 0;
                            SDL_PollEvent(e);
                            if(e -> type == SDL_KEYDOWN)
                            {
                                save_info(current_goal1,current_goal2,players,winner,goals,losses,wins,n,current_player1,current_player2);
                                mainmenu = true;
                                main_game=false;
                                goal1 = false,goal2 = false, entrance_animation = true;
                                break;
                            }

                           text(m_renderer,timet_x,t_y,timet_w,timet_h,0,0,0,40,tostring(t));//time
                text(m_renderer,x_name1,y_name,w_name,h_name,0,0,0,20,current_player1);//player 1 name on score board
                text(m_renderer,x_name2,y_name,w_name,h_name,0,0,0,20,current_player2);//player 2 name on score board
                text(m_renderer,x_score1,y_score,w_score,h_score,0,0,0,20,tostring(current_goal1));//score player 1
                text(m_renderer,x_score2,y_score,w_score,h_score,0,0,0,20,tostring(current_goal2));//score player 1
                         text(m_renderer,570,410,140,35,0,0,0,40,winner);
                            SDL_Delay(20);
                            SDL_RenderPresent(m_renderer);
                        }
                    }
                    else if(current_goal1 <= current_goal2)//player2 wins
                    {
                        string winner = current_player2;
                        Mix_PlayChannel(-1,collision,0);
                        while(true)
                        {
                            double y_audience1 = 390,y_audience2=305,h_audience = 30, x_head2 = player2_x + 37,x_head1=player1_x +72, y_head2 = player2_y - h_head+5,y_head1 = player1_y - h_head+5;
                            string player1 =  "player11.png", player2 = "player21.png",confetti = "confetti";
                            window_color(m_renderer,0,0,0);
                            if(int(q) % 2 ==0 )
                            {
                                y_audience1 -= 10;
                                y_audience2 -= 10;
                                h_audience += 10;
                            }
                            texture(m_renderer,0,0,"soccer stadium1.png",Width,Height);
                            texture(m_renderer,x_audience + 4*115,y_audience1,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 5*115,y_audience1,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 6*115,y_audience1,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 7*115,y_audience1,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience,390,"audience.png",115,30);
                            texture(m_renderer,x_audience + 1*115,390,"audience.png",115,30);
                            texture(m_renderer,x_audience + 2*115,390,"audience.png",115,30);
                            texture(m_renderer,x_audience + 3*115,390,"audience.png",115,30);
                            texture(m_renderer,x_audience+ 4*115,y_audience2,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 5*115,y_audience2,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 6*115,y_audience2,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience + 7*115,y_audience2,"audience.png",115,h_audience);
                            texture(m_renderer,x_audience,305,"audience.png",115,30);
                            texture(m_renderer,x_audience + 1*115,305,"audience.png",115,30);
                            texture(m_renderer,x_audience + 2*115,305,"audience.png",115,30);
                            texture(m_renderer,x_audience + 3*115,305,"audience.png",115,30);
                            texture(m_renderer,powerline1_x,powerline1_y,powerline1,powerline1_w,powerline1_h);
                            texture(m_renderer,powerline2_x,powerline2_y,powerline2,powerline2_w,powerline2_h);



                            ball = temp;
                            ball+="1.png";
                            texture(m_renderer,ball_x,ball_y,ball,w_ball,h_ball);
                            stringstream f;
                            f << q;
                            str = f.str();
                            confetti += str;
                            confetti += ".PNG";
                            texture(m_renderer,player1_x,player1_y,player1,w_body,h_body);
                            texture(m_renderer,player2_x,player2_y,player2,w_body,h_body);
                            texture(m_renderer,x_head1,y_head1,player1_ch,h_head,w_head);
                            texture(m_renderer,x_head2,y_head2,player2_ch,h_head,w_head);
                            texture(m_renderer,0,0,confetti,Width,Height);
                            ad(m_renderer,ad_x1,ad_h,ad_w);
                            texture(m_renderer,460,160,"winnercup.png",360,390);//CUP sign
                            q++;
                            if(q > 16)
                                q = 1;

                            e->type = 0;
                            SDL_PollEvent(e);
                            if(e -> type == SDL_KEYDOWN)
                            {
                                save_info(current_goal1,current_goal2,players,winner,goals,losses,wins,n,current_player1,current_player2);
                                mainmenu = true;
                                main_game=false;
                                goal1 = false,goal2 = false, entrance_animation = true;
                                break;
                            }
                           text(m_renderer,timet_x,t_y,timet_w,timet_h,0,0,0,40,tostring(t));//time
                text(m_renderer,x_name1,y_name,w_name,h_name,0,0,0,20,current_player1);//player 1 name on score board
                text(m_renderer,x_name2,y_name,w_name,h_name,0,0,0,20,current_player2);//player 2 name on score board
                text(m_renderer,x_score1,y_score,w_score,h_score,0,0,0,20,tostring(current_goal1));//score player 1
                text(m_renderer,x_score2,y_score,w_score,h_score,0,0,0,20,tostring(current_goal2));//score player 1
                          text(m_renderer,570,410,140,35,0,0,0,40,winner);
                            SDL_Delay(20);
                            SDL_RenderPresent(m_renderer);
                        }
                    }

                }

                SDL_Delay(20);
                SDL_RenderPresent(m_renderer);

        }
        }

    }


    SDL_RenderClear(m_renderer);
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;

}

void window_color(SDL_Renderer *Renderer, int R, int G, int B)
{

    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
    SDL_RenderClear(Renderer);
}
string tostring(int number){
    stringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}

void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian)
{
    SDL_Rect rectangle ;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
    SDL_RenderFillRect(Renderer, &rectangle);
    SDL_RenderDrawRect(Renderer, &rectangle);
}
void texture(SDL_Renderer *m_renderer,double xp,double yp,string addressOfImage,int width,int height)
{
    int n = addressOfImage.length();
    char char_array[n+1];

    strcpy(char_array, addressOfImage.c_str());
    SDL_Texture *myTexture;
    myTexture = IMG_LoadTexture( m_renderer, char_array);
    int w1, h1;
    SDL_QueryTexture(myTexture, NULL, NULL, &w1, &h1);
    SDL_Rect texr1;
    texr1.x = xp;
    texr1.y = yp;
    texr1.w = width;
    texr1.h = height;
    SDL_RenderCopy( m_renderer, myTexture, NULL, &texr1);
    SDL_DestroyTexture(myTexture);
}

void main_menu(SDL_Renderer *m_renderer,int Width,int Height,bool mainmenu_animation,bool theme1,bool theme2)
{
    double height_menu1=220,width_menu1=600, x_menu1 = ((Width - width_menu1) / 2),y_menu1=0,a_menu1= 1;
    double  height_menu= 100,width_menu= 300,x_menu_even=920,x_menu_odd = 0,a_menu_even = -5,a_menu_odd = 5,y_menu2 = 280;
    SDL_RenderClear(m_renderer);
    double y_menu3 = 400, y_menu4 = 520, y_menu5 = 640,x = ((Width - width_menu) / 2);
    if(mainmenu_animation)
    {
        for(double time = 0; time < 8; time += 1)
        {
            y_menu1=0.5*time*time*a_menu1;
            x_menu_even += 0.5*time*time*a_menu_even;
            x_menu_odd += 0.5*time*time*a_menu_odd;
            window_color(m_renderer,0,0,0);
            texture(m_renderer,0,0,"mainmenubg1.png",1280,800);
            // SDL_Delay(10);
            if(theme1)
            {
                texture(m_renderer,x_menu1,y_menu1,"menu1_t1.PNG",width_menu1,height_menu1);
                texture(m_renderer,x_menu_even,y_menu2,"menu2_t1.PNG",width_menu,height_menu);
                texture(m_renderer,x_menu_odd,y_menu3,"menu3_t1.PNG",width_menu,height_menu);
                texture(m_renderer,x_menu_even,y_menu4,"menu4_t1.PNG",width_menu,height_menu);
                texture(m_renderer,x_menu_odd,y_menu5,"menu5_t1.PNG",width_menu,height_menu);
                SDL_Delay(5);
            }
            else if(theme2)
            {
                texture(m_renderer,x_menu1,y_menu1,"menu1_t2.PNG",width_menu1,height_menu1);
                texture(m_renderer,x_menu_even,y_menu2,"menu2_t2.PNG",width_menu,height_menu);
                texture(m_renderer,x_menu_odd,y_menu3,"menu3_t2.PNG",width_menu,height_menu);
                texture(m_renderer,x_menu_even,y_menu4,"menu4_t2.PNG",width_menu,height_menu);
                texture(m_renderer,x_menu_odd,y_menu5,"menu5_t2.PNG",width_menu,height_menu);
                SDL_Delay(50);
            }

            SDL_RenderPresent( m_renderer );
        }
    }
    if(!mainmenu_animation)
    {

        if(theme1)
        {
            window_color(m_renderer,0,0,0);
            texture(m_renderer,0,0,"mainmenu_theme1.png",1280,800);
        }
        if(theme2)
        {
            window_color(m_renderer,0,0,0);
            texture(m_renderer,0,0,"mainmenu_theme2.png",1280,800);
        }
        SDL_Delay(10);
        SDL_RenderPresent( m_renderer );
    }
}

void text(SDL_Renderer * m_renderer,int x,int y,int width, int height,int R,int G,int B,int FontSize,string input)
{

//    int font = 2;
//    const char * c = Message.c_str();
//    SDL_Color text_color = { R, G, B};
////     textColor(m_renderer,xp,yp,c,font,Size,text_color);
////textRGBA(m_renderer, xp, yp, c, font, Size, R, G, B, 255);
////SDL_RenderPresent( m_renderer );

    string FontAddress = "arial.ttf";
    TTF_Init();
    SDL_Color foreground = {R,G,B};
    SDL_Rect dest;
    TTF_Font* font = TTF_OpenFont(FontAddress.c_str(),FontSize);
    SDL_Surface* text_surf = TTF_RenderText_Solid(font, input.c_str(), foreground);
    SDL_Texture* text = SDL_CreateTextureFromSurface(m_renderer, text_surf);

    dest.x = x;
    dest.y = y;
    dest.w = text_surf->w;
    dest.h = text_surf->h;
    SDL_RenderCopy(m_renderer, text, NULL, &dest);

    SDL_DestroyTexture(text);
    SDL_FreeSurface(text_surf);

  TTF_CloseFont( font );
    TTF_Quit();

}

void setting(SDL_Renderer * m_renderer,int x_setting_L, int x_setting_R, int y_setting_U,int y_setting_D,int a)
{
    window_color(m_renderer,0,0,0);
    texture(m_renderer,0,0,"setting.png",1280,800);
//    rect(m_renderer,185,170,810,500,0,0,139,0);
//    texture(m_renderer,0,0,"mainmenubg1.png",1280,800);
//    texture(m_renderer,350,180,"board.png",579,431);
//    texture(m_renderer,x_setting_L,y_setting_U,"mute.png",a,a);
//    texture(m_renderer,x_setting_R,y_setting_U,"unmute.png",a,a);
//    texture(m_renderer,x_setting_L,y_setting_D,"theme2.JPEG",a,a);
//    texture(m_renderer,x_setting_R,y_setting_D,"theme1.JPEG",a,a);
//    text(m_renderer,430,280,170,50,255,255,255,40,"Sound : ");
//    text(m_renderer,430,450,170,50,255,255,255,40,"Theme : ");
//    SDL_Delay(50);
   // SDL_RenderPresent( m_renderer );
}

void league(SDL_Renderer * m_renderer,string players[],string wins[],string losses[],string goals[],int n)
{

    int x1_o= 390, y_o = 120,x2_o =830,L_H = 50, L_V = 110, x_a = 390, y1_a = 120;//table info
    int counter=0;//number of all players
    int x_playername = 400, x_wins = x_playername + 120, x_losses = x_wins + 98, x_goals = x_losses + 120;//playesr info
    int y_playerinfo = 183, width_playername = 160, height_info = 60, width_info = 80;

    // window_color(m_renderer,0,0,0);
    for(int i = 0; i <= n; i++)
        if(players[i] != "")
            counter++;

    int y2_a = ((counter+1) * L_H) + y1_a;//table info

    for(int i=0; i<=counter + 1; i++) //Horizontal lines
        aalineRGBA(m_renderer,x1_o,y_o + (i * L_H),x2_o,y_o +(i * L_H),0,255,255,255);
    for(int i = 0; i < 5; i++)//Vertical lines
        aalineRGBA(m_renderer,x_a + (i * L_V),y1_a,x_a + (i * L_V),y2_a,255,0,255,255);
    texture(m_renderer,410,5,"league.png",400,110);
    text(m_renderer,x_playername-4,125,width_playername,height_info,255,255,255,30,"Names");
    text(m_renderer,x_wins,125,width_info,height_info,255,255,255,30,"Wins");
    text(m_renderer,x_losses,125,width_info,height_info,255,255,255,30,"Losses");
    text(m_renderer,x_goals,125,width_info,height_info,255,255,255,30,"Goals");
    SDL_Delay(20);
    for(int i =0 ; i < counter; i++)
    {
        if(players[i] != "")
        {
            text(m_renderer,x_playername,y_playerinfo - 3 + (i * L_H),width_playername,height_info,150,150,255,25,players[i]);
            text(m_renderer,x_wins+30,y_playerinfo + (i * L_H), width_info, height_info,150,255,150,20,wins[i]);
            text(m_renderer,x_losses+43,y_playerinfo + (i * L_H), width_info, height_info,150,255,150,20,losses[i]);
            text(m_renderer,x_goals+35,y_playerinfo + (i * L_H), width_info, height_info,150,255,150,20,goals[i]);
            SDL_Delay(10);
        }
    }
    SDL_Delay(20);

    SDL_RenderPresent(m_renderer);

}

void start(SDL_Renderer * m_renderer)
{
    int x_rm=760, x_rw = 990, x_bm = 360, x_bw = 100, y_ch = 190, height_ch=200,width_rm = 160,width_rw=140,width_bw= 170,width_bm = 120;
    int L = 100, width_b = 130, x_b1 = 100, x_b2 = x_b1 + L + width_b, x_b3 = x_b1, x_b4 = x_b2, y_b12 = 465,y_b34 = y_b12+width_b + 50, height_b = 130;
    int x_90or5=520,w_90or5 = 236,h_90or5 = 290;
    texture(m_renderer,0,0,"start.png",1280,800);
}

void typing(SDL_Renderer * m_renderer,SDL_Event * e,string &current_player,int x_p)
{
    int  y_p =43, w_p = 100, h_p = 10,Size = 60;
    switch(e ->key.keysym.sym)
    {
    case SDLK_a :
        current_player += "a";
        break;
    case SDLK_b :
        current_player += "b";
        break;
    case SDLK_c :
        current_player += "c";
        break;
    case SDLK_d :
        current_player += "d";
        break;
    case SDLK_e :
        current_player += "e";
        break;
    case SDLK_f :
        current_player += "f";
        break;
    case SDLK_g :
        current_player += "g";
        break;
    case SDLK_h :
        current_player += "h";
        break;
    case SDLK_i :
        current_player += "i";
        break;
    case SDLK_j :
        current_player += "j";
        break;
    case SDLK_k :
        current_player += "k";
        break;
    case SDLK_l :
        current_player += "l";
        break;
    case SDLK_m :
        current_player += "m";
        break;
    case SDLK_n :
        current_player += "n";
        break;
    case SDLK_o :
        current_player += "o";
        break;
    case SDLK_p :
        current_player += "p";
        break;
    case SDLK_q :
        current_player += "q";
        break;
    case SDLK_r :
        current_player += "r";
        break;
    case SDLK_s :
        current_player += "s";
        break;
    case SDLK_t :
        current_player += "t";
        break;
    case SDLK_u :
        current_player += "u";
        break;
    case SDLK_v :
        current_player += "v";
        break;
    case SDLK_w :
        current_player += "w";
        break;
    case SDLK_x :
        current_player += "x";
        break;
    case SDLK_y :
        current_player += "y";
        break;
    case SDLK_z :
        current_player += "z";
        break;
    }
    text(m_renderer,x_p,y_p,w_p,h_p,0,0,0,Size,current_player);
    SDL_Delay( 10);
    SDL_RenderPresent(m_renderer);
}
void ad(SDL_Renderer *m_renderer,int &ad_x1,int ad_h,int ad_w)
{
    int ad_x2=ad_x1-ad_w;
    if(ad_x1+3<=ad_w)
    {
        ad_x1+=3;
    }
    else
    {
        ad_x1=0;
    }
    texture(m_renderer,ad_x1,730,"ad.png",ad_w,ad_h);
    texture(m_renderer,ad_x2,730,"ad.png",ad_w,ad_h);

}
void save_info(int &current_goals1,int &current_goals2,string players[],string winner,string goals[],string losses[],string wins[],int &n,string current_player1,string current_player2)
{
    bool New1 = true;
//    for(int f=0; f<n; f++)
//    {
//        if(current_player1==players[f])
//        {
//            New1 = false;
//            current_goals1 += stoi(goals[f]);
//            goals[f]=tostring(current_goals1);
//            if(winner == current_player1)
//            {
//                int p = stoi(wins[f])+1;
//                wins[f]=to_string(p);
//            }
//            else if(winner == current_player2)
//            {
//                int p = stoi(losses[f])+1;
//                losses[f]=to_string(p);
//            }
//            break;
//        }
//    }
//n++;
    if(New1)
    {
        players[n]=current_player1;
        current_goals1 += stoi(goals[n]);
        goals[n]=to_string(current_goals1);
        if(winner == current_player1)
        {
            int p = stoi(wins[n])+1;
            wins[n]=to_string(p);
           // cout<<wins[n]<<endl;
        }
        else if(winner == current_player2)
        {
            int p = stoi(losses[n])+1;
            losses[n]=to_string(p);
           // cout<<losses[n]<<endl;
        }
        n++;
    }
    bool New2 = true;
//    for(int f=0; f<n; f++)
//    {
//        if(current_player2==players[f])
//        {
//            New2 = false;
//            current_goals2 += stoi(goals[f]);
//            goals[f]=to_string(current_goals2);
//            if(winner == current_player2)
//            {
//                int p = stoi(wins[f])+1;
//                wins[f]=to_string(p);
//            }
//            else if(winner == current_player1)
//            {
//                int p = stoi(losses[f])+1;
//                losses[f]=to_string(p);
//            }
//            break;
//        }
//    }
    if(New2)
    {
        players[n]=current_player2;
        current_goals2 += stoi(goals[n]);
        goals[n]=to_string(current_goals2);
        if(winner == current_player2)
        {
            int p = stoi(wins[n])+1;
            wins[n]=to_string(p);
        }
        else if(winner == current_player1)
        {
            int p = stoi(losses[n])+1;
            losses[n]=to_string(p);
        }
       // n++;
    }
//    if(!New1 && New2)
//    {
//        players[n-1]=players[n];
//        players[n]="";
//        losses[n-1]==losses[n];
//        losses[n]="";
//        wins[n-1]=wins[n];
//        wins[n]="";
//        goals[n-1]=goals[n];
//        goals[n]="";
//    }
//    int p;
//    if(New1 && New2)
//        p = n+1;
//    else if(New1 && !New2)
//    {
//        p = n;
//        players[n]="";
//    }
//    else if(!New1 && New2)
//    {
//        p = n;
//        players[n-1]="";
//    }
//    else
//    {
//        p = n - 1;
//        players[n]="";
//        players[n-1]="";
//    }
    ofstream output;
    output.open("records.txt",ofstream::out | ofstream::trunc);
    for(int i=0; i<= n; i++)
    {
        if(players[i]!=" " || players[i] != ""){
            output<<players[i];
            output<<" ";
            output<<wins[i];
            output<<" ";
            output<<losses[i];
            output<<" ";
            output<<goals[i];
            output<<" ";
        }

    }
    output.close();
    current_goals1 = 0;
    current_goals2 = 0;
   // n++;

}

