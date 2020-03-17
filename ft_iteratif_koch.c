#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>
#include <time.h>
 
double arrondir(double V,double A);
double convertirCoordonneeX(double X);
double convertirCoordonneeY(double Y);
void pause();
void creerFenetre(int W,int H,int R,int V,int B);
void dessinerPixel(double X,double Y,int W,int H,int R,int V,int B,int D);
void dessinerDroiteAffine(double X1,double Y1,double X2,double Y2,int R,int V,int B,int D);
void dessinerAxes();
 
SDL_Surface *ecran = NULL;
SDL_Surface *pixel = NULL;
 
int W=600,H=450;
 
int main(int argc,char *argv[])
{  
    double Pi=atan(1);
     
    int n=3;
     
    int Ki=0;
    int Kr=0;
    int Ks=0;
    int Kp=0;
    int Kc=0;
    int Kt=0;
     
    double X1,Y1;
    double X2,Y2;
    double X3,Y3;
    double X4,Y4;
    double X5,Y5;
     
    int iteration=1;
     
    int nombreDIterations=1;
     
    int nombreDePoints;
     
    const int nombreDePointsTotal=n*pow(4,nombreDIterations);
     
    double coordonneeX[nombreDePointsTotal];
    double coordonneeY[nombreDePointsTotal];
     
    double coordonneeXSauvegarde[nombreDePointsTotal];
    double coordonneeYSauvegarde[nombreDePointsTotal];
     
    SDL_Init(SDL_INIT_VIDEO);
     
    creerFenetre(W,H,128,128,128);
     
    dessinerAxes();
     
//Initialisation des tableaux//
     
    while(Ki<=nombreDePointsTotal)
    {
        coordonneeX[Ki]=coordonneeXSauvegarde[Ki]=0.000;
        coordonneeY[Ki]=coordonneeYSauvegarde[Ki]=0.000;
         
        Ki++;
    }
     
//Racines n-iemes//
 
    while(Kr<=(n+1))
    {
        if(Kr!=(n+1))
        {
            coordonneeX[Kr]=cos(2*(Kr)*4*Pi/n)*200;
            coordonneeY[Kr]=sin(2*(Kr)*4*Pi/n)*200;
        }
        else
        {
            coordonneeX[Kr]=coordonneeX[0];
            coordonneeY[Kr]=coordonneeY[0];
        }
         
        Kr++;
    }
     
//Algorithme fractale//
     
    while(iteration<=nombreDIterations)
    {
        //Sauvegarde des tableaux//
         
        while(Ks<=nombreDePointsTotal)
        {
            coordonneeXSauvegarde[Ks]=coordonneeX[Ks];
            coordonneeX[Ks]=0;
             
            coordonneeYSauvegarde[Ks]=coordonneeY[Ks];
            coordonneeY[Ks]=0;
             
            Ks++;
        }
         
        Ks=0;
         
        //Calculs des coordonnees//
         
        nombreDePoints=n*pow(4,iteration-1);
         
        while(Kp<=nombreDePoints)
        {
            if(Kp==nombreDePoints)
            {
                coordonneeX[Kc]=coordonneeXSauvegarde[0];
                coordonneeY[Kc]=coordonneeYSauvegarde[0];
            }
            else
            {
                X1=arrondir(coordonneeXSauvegarde[Kp],0.001);
                Y1=arrondir(coordonneeYSauvegarde[Kp],0.001);
             
                X2=arrondir(coordonneeXSauvegarde[Kp+1],0.001);
                Y2=arrondir(coordonneeYSauvegarde[Kp+1],0.001);
             
                X3=arrondir(2/3*X1+1/3*X2,0.001);
                Y3=arrondir(2/3*Y1+1/3*Y2,0.001);
             
                X4=arrondir(0.5*(X1+X2+sqrt(3)/3*(Y2-Y1)),0.001);
                Y4=arrondir(0.5*(Y1+Y2+sqrt(3)/3*(X1-X2)),0.001);
             
                X5=arrondir(1/3*X1+2/3*X2,0.001);
                Y5=arrondir(1/3*Y1+2/3*Y2,0.001);
             
                coordonneeX[Kc]=X1;
                coordonneeY[Kc]=Y1;
             
                coordonneeX[Kc+1]=X3;
                coordonneeY[Kc+1]=Y3;
             
                coordonneeX[Kc+2]=X4;
                coordonneeY[Kc+2]=Y4;
             
                coordonneeX[Kc+3]=X5;
                coordonneeY[Kc+3]=Y5;
            }
                         
            Kp+=1;
            Kc+=4;
        }
         
        iteration+=1;
 
    }
     
//Tracage//
     
    while(Kt<nombreDePointsTotal)
    {
        dessinerDroiteAffine(coordonneeX[Kt],coordonneeY[Kt],coordonneeX[Kt+1],coordonneeY[Kt+1],255,000,000,1);
         
        Kt++;
    }
 
    //dessinerAxes();
     
    pause();
     
    SDL_Quit();
     
    return EXIT_SUCCESS;
}
 
double arrondir(double V,double A)
{
    return floor(V*(1/A)+0.5)/(1/A);
}
 
double convertirCoordonneeX(double X)
{
    return X=W/2+X;
}
 
double convertirCoordonneeY(double Y)
{
    return Y=H/2-Y;
}
 
void creerFenetre(int W,int H,int R,int V,int B)
{
    ecran = SDL_SetVideoMode(W,H,32,SDL_HWSURFACE);
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,R,V,B));
    SDL_Flip(ecran);
}
 
void pause()
{
    int continuer = 1;
     
    SDL_Event event;
     
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0; 
        }
    }
}
 
void dessinerPixel(double X,double Y,int W,int H,int R,int V,int B,int D)
{
    SDL_Rect coordonnee;
     
    coordonnee.x=convertirCoordonneeX(X);
    coordonnee.y=convertirCoordonneeY(Y);
     
    pixel = SDL_CreateRGBSurface(SDL_HWSURFACE,W,H,32,0,0,0,0);
    SDL_FillRect(pixel,NULL,SDL_MapRGB(pixel->format,R,V,B));
     
    SDL_BlitSurface(pixel,NULL,ecran,&coordonnee);
     
    if(D==1)
    {
        SDL_Flip(ecran);
    }
     
    SDL_FreeSurface(pixel);
}
 
void dessinerDroiteAffine(double X1,double Y1,double X2,double Y2,int R,int V,int B,int D)
{
    X1=arrondir(X1,0.001);
    Y1=arrondir(Y1,0.001);
    X2=arrondir(X2,0.001);
    Y2=arrondir(Y2,0.001);
     
    if((X1!=X2)&&(Y1!=Y2))
    {
        double a=arrondir((Y2-Y1)/(X2-X1),0.001);
        double b=arrondir(Y2-a*X2,0.001);
         
        double X=X1;
         
        if(X1<X2)
        {
            while(X<=X2)
            {
                dessinerPixel(X,a*X+b,1,1,R,V,B,D);
                 
                X+=1;
            }
        }
        else
        {
            while(X>=X2)
            {
                dessinerPixel(X,a*X+b,1,1,R,V,B,D);
                 
                X-=1;
            }
        }
    }
    else
    {
        if((X1==X2)&&(Y1!=Y2))
        {
            double Y=Y1;
             
            if(Y1<Y2)
            {
                while(Y<=Y2)
                {
                    dessinerPixel(X1,Y,1,1,R,V,B,D);
                     
                    Y+=1;
                }
            }
            else
            {
                while(Y>=Y2)
                {
                    dessinerPixel(X1,Y,1,1,R,V,B,D);
                     
                    Y-=1;
                }
            }
        }
        else if((X1!=X2)&&(Y1==Y2))
        {
            double X=X1;
             
            if(X1<X2)
            {
                while(X<=X2)
                {
                    dessinerPixel(X,Y1,1,1,R,V,B,D);
                     
                    X+=1;
                }
            }
            else
            {
                while(X<=X2)
                {
                    dessinerPixel(X,Y1,1,1,R,V,B,D);
                     
                    X-=1;
                }
            }
        }
    }
    if(D==0)
    {
        SDL_Flip(ecran);
    }
}
 
void dessinerAxes()
{
    dessinerDroiteAffine(0,-H/2,0,H/2,000,000,000,0);
    dessinerDroiteAffine(-W/2,0,W/2,0,000,000,000,0);
}
