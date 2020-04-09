#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <jerror.h>
#include <jpeglib.h>
#include <setjmp.h>
#define X_SIZE  700 
#define Y_SIZE  600 
/*#define DR 150
#define DG 200
#define DB 255 */
#define NR 0
#define NB 10
#define NG 0

/* here are our X variables */
Display *display;
int screen;
Window win;
GC gc;
XImage *x_image;
unsigned char *x_buffer;

int mr,mg,mb;

/* here are our X routines declared! */
void init_x();
void close_x();
void redraw();
void fence(int);
void clear(int);
int line(int,int,int,int,int,int,int,int,int,int);
int cloud(int,int,int,int);
int bow (int,int,int,float,int,int,int,int,int,int);
int sun (int,int,int,int);
int star (int,int,int,int,int,int,int);
int moon (int,int,int,int,int);
int hole (int,int,int,int,int,int,int);
void flower (int,int,int,int);
static int XS=X_SIZE*4;
static int XM=X_SIZE*Y_SIZE*4;
static int JS=X_SIZE*3;
static int rr[7]={ 255,255,255,0,0,75,238 };
static int gg[7]={ 0,165,255,128,0,0,130 };
static int bb[7]={ 0,0,0,0,255,130,238 }; 
unsigned char *jay;
int DR,DG,DB;


/* Jpegs */
int read_JPEG_file (char *, unsigned char *, int *);
int jayit(unsigned char *,int, int, char *);

void usage ()
{
	printf("usage: git\n");
	exit (1);
}


int main(int argc,char *argv[])
{
	init_x();
	char fname[100],dum;
	int x,y,c,sz,col;
	float f;
	c=0;
	DR=rr[4]; DG=gg[4]; DB=bb[4];

	jay=(char *)malloc(sizeof(char)*3*X_SIZE*Y_SIZE);
	int fe,xs,ys,xm,ym,g,lx,ly,ll,la,nlx,nly;
	int bx,by;
	xs=640;ys=60;
	xm=85;ym=85;


	int sp[4][800];
	int st[4][800];
	//shrink and left
	for (g=300;g<=300;g+=5)
	{
		clear(300);
		bow((X_SIZE/2)+g,Y_SIZE-1,360-g,0,100,300-g/4,0,0,90,700);
		sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname); 
		XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
	}
	// wiggle up
	for (g=0;g<=355;g+=4)
	{
		clear(300);
		bx=(X_SIZE/2)+300-((1*X_SIZE*sin((2*M_PI*g)/143))/6)-g;
		by=Y_SIZE-((11*g)/8);
		bow(bx,by,60,0,100,300,0,0,90,700);
		sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname); 
		XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
	}
	// grow and turn
        for (g=0;g<=100;g+=2)
        {
                clear(300);
                bow(bx,by,60+((g*6)/4),g/2,100,300,0,0,90,700);
                sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname); 
                XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
        }
	// donate to moon
       for (g=1;g<=100;g+=1)
        {
                clear(300);
                bow(bx,by,64+(600/4),50,100,300,0,0,90,695-g);
                moon (xm,ym,80,300-(g*3),g/3);
                sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname);
                XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
        }
	// turn and shrink
        for (g=100;g>0;g-=4)
        {
                clear(300);
                bow(bx,by,60+((g*6)/4),g/3,100,300,0,0,90,588);
                moon (xm,ym,80,0,33);
                sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname);
                XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
        }
	// move to bottom left 
	int bxr,byr,bnx,bny;
	bxr=150;byr=Y_SIZE-150;
        for (g=1;g<100;g++)
        {
                clear(300);
		bnx=bx-((g*(bx-bxr))/100);
		bny=by-((g*(by-byr))/100);
                bow(bnx,bny,60+(4*g/3),0,100,300,0,0,90,590);
                moon (xm,ym,80,0,33);
                sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname);
                XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
        }
	// shoot stars
//int line (int x,int y,int ang, int t, int le, int r, int g, int b, int day, int eeta )
        for (fe=0;fe<800;fe++){ sp[0][fe]=rand()%X_SIZE;sp[1][fe]=(rand()%(Y_SIZE/2)); sp[2][fe]=2+rand()%5; sp[3][fe]=rand()%7;}
        for (g=0;g<400;g+=2)
        {
		float thee;
		int length;
		length=rand()%900;
		thee=90+(g/2);
                clear(300);
		//line (bxr,Y_SIZE-1-byr,-thee,2,length,rr[5],gg[5],bb[5],300,0);
		sp[0][g]=bxr-(length*sin((thee*2*M_PI)/360));
		sp[1][g]=byr+(length*cos((thee*2*M_PI)/360));
        	for (fe=0;fe<g;fe+=1)
		{ 
			star (sp[0][fe],sp[1][fe],sp[2][fe],rr[5],gg[5],bb[5],0);
		}
                moon (xm,ym,80,0,33);
                bow(bxr,byr,60+(400/3),thee,100,300,0,0,90,590-(g/4));
                sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname);
                XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
        }
	// go blue
        for (g=0;g<100;g++)
        {
                clear(300-g*3);
                for (fe=0;fe<400;fe+=1)
                {
                        star (sp[0][fe],sp[1][fe],5,rr[5],gg[5],bb[5],g*3);
                }
                moon (xm,ym,80,g*3,33);
                bow(bxr--,byr--,60+(400/3),g,100,300,0,0,90,490-g);
                sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname);
                XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
        }
	//green
	for (g=0;g<=100;g+=1)
	{
		clear(0);
		line (7*g,0,180,7*g,300,rr[3],gg[3],bb[3],300,0); 
                bow(bxr+(g*2),byr,60+(400/3),100-g,100,300,0,0,90,390-g);
		sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname); 
		XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
	}
	bxr+=g*2;
	// go to sun
        for (g=0;g<100;g++)
        {
                clear(0);
		line (700,0,180,700,300,rr[3],gg[3],bb[3],300,0); 
                bnx=bxr+((g*(xs-bxr))/100);
                bny=byr+((g*(ys-byr))/100);
                bow(bnx,bny,60+(100-g),0,100,300,0,0,90,290);
                sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname);
                XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
        }

	// make sun
        for (g=0;g<100;g++)
        {
                clear(0);
                line (700,0,180,700,300,rr[3],gg[3],bb[3],300,0);
                bow(xs,ys,60+g,g*4,100,300,0,0,90,290-g);
		sun(xs,ys,50,300-(g*3));
                sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname);
                XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
        }

	// colour fence
        for (g=0;g<100;g++)
        {
                clear(0);
                line (700,0,180,700,300,rr[3],gg[3],bb[3],300,0);
                sun(xs,ys,50,0);
                fence(g*3);
                bow(g*3,Y_SIZE/2,300,90,100,300,0,0,90,190-g);
                sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname);
                XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
        }
	// smile
        for (fe=0;fe<800;fe++){ sp[0][fe]=rand()%X_SIZE;sp[1][fe]=(rand()%(Y_SIZE/2)); sp[2][fe]=rand()%90; sp[3][fe]=rand()%7;}
	sp[3][0]=0;
        for (g=0;g<=100;g++)
        {
                clear(0);
                line (700,0,180,700,300,rr[3],gg[3],bb[3],300,0);
                sun(xs,ys,50,0);
        	for (fe=0;fe<4*g;fe+=1)
		{ 
			flower (sp[0][fe],sp[1][fe],sp[2][fe],0);
		}
                fence(300);
//int bow (int x,int y, int r, float thetam, int per,int day, int freq, int depth, int height,int cols)
                bow(300,Y_SIZE/2,305-(3*g),90-g,100+g,300,500,5-((100-g)/25),90,90);
                sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname);
                XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
        }
	// returm
	int hold;
	hold=0;
        for (g=0;g<100;g++)
        {
                clear(0);
                line (700,0,180,700,300,rr[3],gg[3],bb[3],300,0);
                bow(300,Y_SIZE/2,g*3,0,100,300,0,0,90,700);
                sun(xs,ys,50,0);
                for (fe=0;fe<=400;fe+=1)
                {
                        flower (sp[0][fe],sp[1][fe],sp[2][fe],sp[3][(((7*fe)/40)*(g/10))/100]);
                }
                fence(300);
                sprintf(fname,"nrain%04d.jpg",c);c++;jayit(jay,X_SIZE,Y_SIZE,fname);
                XPutImage(display, win, gc, x_image, 0, 0, 0, 0, X_SIZE, Y_SIZE);
		if (g==99 && hold < 50){ g=98; hold++;}
        }

	scanf("%c",&dum);
}


void flower (int x,int y, int sz, int col)
{
	line (x,y,180,2,sz,0,200,0,300,1);
	line (x,y,160,1,sz/2,0,90,0,300,0);
	line (x,y,200,1,sz/2,0,90,0,300,0);
//int star (int x,int y, int r, int rr, int gg, int bb,int day)
	int yp;
	yp=Y_SIZE-y-sz;
	if (yp<Y_SIZE/2 && col==4){ col=2;}
	if (yp>Y_SIZE/2 && col==2){ col=4;}
	star (x,yp,sz/5,rr[col],gg[col],bb[col],0);
}



void fence (int day)
{
	int fe;
	                //posts
                line (30,0,180,25,200,rr[1],gg[1],bb[1],day,0); line (180,0,180,25,200,rr[1],gg[1],bb[1],day,0);
                line (330,0,180,25,200,rr[1],gg[1],bb[1],day,0); line (480,0,180,25,200,rr[1],gg[1],bb[1],day,0); line (699,0,180,25,200,rr[1],gg[1],bb[1],day,0);
                //aris
                line (0,10,90,16,480,rr[1],gg[1],bb[1],day,0); line (0,160,90,16,480,rr[1],gg[1],bb[1],day,0);
                //feathers
                for (fe=50;fe<480;fe+=30){ line (fe,10,180,10,180,rr[1],gg[1],bb[1],day,0); }
                //gate
                for (fe=500;fe<690;fe+=29){ line (fe,10,180,10,180,rr[1],gg[1],bb[1],day,0); }
                line (490,10,90,10,180,rr[1],gg[1],bb[1],day,0); line (490,160,90,10,180,rr[1],gg[1],bb[1],day,0);
                line (499,13,130,10,219,rr[1],gg[1],bb[1],day,0);
}



int cloud (int x,int y, int rmax, int day)
{
        int rmin,xmax,ymax,xmin,ymin,xp,yp,night;
        rmin=3*rmax/6;
	night=300-day;

        float rads,dtheta,ftheta,pi;
        pi=(M_PI/2);

        dtheta=asin(1/(2*(float)rmax));

        for (rads=1;rads<rmax;rads+=0.9)
        {
                dtheta=asin(1/(2*rads));
        	for (ftheta=0;ftheta<4*pi;ftheta+=dtheta)
                {
                        int P,J;
                        float roff;
                        roff=1+(sin(ftheta*rmax/7));
                        roff=roff*6;
                        xp=x+((rads-roff)*sin(ftheta));
                        yp=y-(((rads-roff)*cos(ftheta)/2));
			if (xp<X_SIZE && yp < Y_SIZE && xp>0 && yp > 0)
			{
                        P=((xp*4)+(yp*XS));
                        J=((xp*3)+(yp*JS));
	                x_buffer[P]=((255*(night))/300)+((day*20)/300);
                        x_buffer[P+1]=((255*(night))/300)+((day*20)/300);
                        x_buffer[P+2]=((255*(night))/300)+((day*20)/300);
                        jay[J]=x_buffer[P+2];
                        jay[J+1]=x_buffer[P+1];
                        jay[J+2]=x_buffer[P];
			}
                }
        }
        return 0;
}

int line (int x,int y,int ang, int t, int le, int r, int g, int b, int day, int eeta )
{
        int night,xe,ye,xte,yte;
        float along,tt,xt,yt,len,tx,ty,xd,yd,ta,ex,ey;
        len=le;
        night=300-day;
        y=Y_SIZE-y-1;

        xd=(len*sin(2*M_PI*ang/360));
        xe=x+xd;
        yd=(len*cos(2*M_PI*ang/360));
        ye=y+yd;

	ex=xd*eeta/len;
	ey=yd*eeta/len;

        tx=(t*sin(2*M_PI*(ang+90)/360));
        ty=(t*cos(2*M_PI*(ang+90)/360));
        xt=x+tx;
        yt=y+ty;
        xte=xe+tx+ex;
        yte=ye+ty+ey;

        /*if ( x> X_SIZE-1 || y> Y_SIZE-1 || x<0 || y< 0 ){ return 1;}
        if ( xe> X_SIZE-1 || ye> Y_SIZE-1 || xe<0 || ye< 0 ){ return 1;}
        if ( xt> X_SIZE-1 || yt> Y_SIZE-1 || xt<0 || yt< 0 ){ return 1;}
        if ( xte> X_SIZE-1 || yte> Y_SIZE-1 || xte<0 || yte< 0 ){ return 1;} */

        for (tt=0;tt<t;tt+=0.4)
        {
                int xs,ys,xp,yp;
		float xpl,ypl;
                //xs=x+(((tx)*tt)/t);ys=y+(((yt-y)*tt)/t);
		//xd=x-xe-((tx*(t-tt))/t);yd=y-ye-((ty*(t-tt))/t);
		//yd=y-ye; xd=x-xe;
		xs=x+(((tx+ex)*tt)/t);ys=y+(((ty+ey)*tt)/t);
		//xpl=xd-(2*tx*tt/t);
		xpl=xd-(2*ex*tt/t);
		ypl=yd-(2*ey*tt/t);
                for (along=0;along<len;along+=0.4)
                {
                int P,J;
                xp=xs+((xpl*along)/len);
                yp=ys+((ypl*along)/len);
                P=((xp*4)+(yp*XS)); J=((xp*3)+(yp*JS));
		if (xp<X_SIZE && yp < Y_SIZE && xp>0 && yp > 0)
		{
                x_buffer[P]=((mb*(night))/300)+((day*b)/300);
                x_buffer[P+1]=((mg*(night))/300)+((day*g)/300);
                x_buffer[P+2]=((mr*(night))/300)+((day*r)/300);
                jay[J]=x_buffer[P+2]; jay[J+1]=x_buffer[P+1]; jay[J+2]=x_buffer[P];
		}
                }
        }
        return 0;
}

int bow (int x,int y, int r, float thetam, int per,int day, int freq, int depth, int height,int cols)
{
	int i,rmin,xmax,ymax,xmin,ymin,xp,yp,night,crmin;
	float rads,dtheta,ftheta,pi,max,theta;
	rmin=5*r/12;
	night=300-day;

	theta=(thetam*M_PI)/180;

	crmin=rmin+(((r-rmin)*(700-cols))/700);

	pi=(M_PI/2);
	
	dtheta=asin(1/(2*(float)r));

	//printf ("checking \n");
	max=((2*pi*per)/100)-pi;

	//printf ("checked \n");
	float f,b;
	f=rand()%10;
	b=rand()%50;
	b=(100-b)/100;
	for (rads=r;rads>crmin;rads-=0.8)
	{
		i=7-(7*(rads-rmin)/(r-rmin));
		dtheta=asin(1/(2*rads));
		for (ftheta=theta-pi;ftheta<theta+max;ftheta+=dtheta)
		{
			int P,J;
			float roff;
			roff=depth*(sin(ftheta*freq/100));
			xp=x+((rads-roff)*sin(ftheta));
			yp=y-((height*((rads-roff)*cos(ftheta)))/100);
			if (xp<X_SIZE && yp < Y_SIZE && xp>0 && yp > 0)
			{
			P=((xp*4)+(yp*XS));
			J=((xp*3)+(yp*JS));
			x_buffer[P]=((bb[i]*day)/300)+(((night)*mb)/300);
			x_buffer[P+1]=((gg[i]*day)/300)+(((night)*mg)/300);
			x_buffer[P+2]=((rr[i]*day)/300)+(((night)*mr)/300);
			jay[J]=x_buffer[P+2];
			jay[J+1]=x_buffer[P+1];
			jay[J+2]=x_buffer[P];
			}
		}
	}
	return 0;
}	

int sun (int x,int y, int r,int day)
{

        float rads,dtheta,ftheta,night;
	int xp,yp;

	night=300-day;

        dtheta=asin(1/(2*(float)r));

        //printf ("checking \n");
        for (ftheta=0;ftheta<2*M_PI;ftheta+=dtheta)
        {
                xp=x+(r*sin(ftheta));
                yp=y+(r*cos(ftheta));
                if (xp<0 || xp>=X_SIZE){ return 1; }
                if (yp<0 || yp>=Y_SIZE){ return 1; }
        }

        //printf ("checked \n");
        for (rads=r;rads>0.5;rads-=0.5)
        {
                dtheta=asin(1/(2*rads));
                for (ftheta=0;ftheta<2*M_PI;ftheta+=dtheta)
                {
                        int P,J;
                        float roff;
                        roff=1+(sin(ftheta*0));
                        roff=roff*3;
                        xp=x+((rads-roff)*sin(ftheta));
                        yp=y+(((rads-roff)*cos(ftheta)));
                        P=((xp*4)+(yp*XS));
                        J=((xp*3)+(yp*JS));

	                x_buffer[P]=((0*(night))/300)+((day*mb)/300);
                        x_buffer[P+1]=((255*(night))/300)+((day*mg)/300);
                        x_buffer[P+2]=((255*(night))/300)+((day*mr)/300);
                        jay[J]=x_buffer[P+2];
                        jay[J+1]=x_buffer[P+1];
                        jay[J+2]=x_buffer[P];
                }
        }
        return 0;
}


int star (int x,int y, int r, int rr, int gg, int bb,int day)
{

        float rads,dtheta,ftheta;
        int xp,yp,night;

	night=300-day;

        dtheta=asin(1/(2*(float)r));

        for (rads=r;rads>0.5;rads-=0.5)
        {
                dtheta=asin(1/(2*rads));
                for (ftheta=0;ftheta<2*M_PI;ftheta+=dtheta)
                {
                        int P,J;
                        float roff;
                        roff=1+(sin(ftheta*6));
                        roff=roff*2;
                        xp=x+((rads-roff)*sin(ftheta));
                        yp=y+(((rads-roff)*cos(ftheta)));
			if (xp<X_SIZE && yp < Y_SIZE && xp>0 && yp > 0)
			{
                        P=((xp*4)+(yp*XS));
                        J=((xp*3)+(yp*JS));
                        x_buffer[P]=((bb*(night))/300)+((day*DB)/300);
                        x_buffer[P+1]=((gg*(night))/300)+((day*DG)/300);
                        x_buffer[P+2]=((rr*(night))/300)+((day*DR)/300);
                        jay[J]=x_buffer[P+2];
                        jay[J+1]=x_buffer[P+1];
                        jay[J+2]=x_buffer[P];
			}
                }
        }
        return 0;
}


int hole (int x,int y, int r,int elipse, int rr, int g, int b)
{

        float rads,dtheta,ftheta;
        int xp,yp;

        dtheta=asin(1/(2*(float)r));

        for (rads=r;rads>0.5;rads-=0.5)
        {
                dtheta=asin(1/(2*rads));
                for (ftheta=0;ftheta<2*M_PI;ftheta+=dtheta)
                {
                        int P,J;
                        float roff;
                        roff=1+(sin(ftheta*6));
                        roff=roff*2;
                        xp=x+((rads-roff)*sin(ftheta));
                        yp=y+((elipse*((rads-roff)*cos(ftheta)))/100);
                        if (xp<X_SIZE && yp < Y_SIZE && xp>0 && yp > 0)
                        {
                        P=((xp*4)+(yp*XS));
                        J=((xp*3)+(yp*JS));
                        x_buffer[P]=b;
                        x_buffer[P+1]=g;
                        x_buffer[P+2]=rr;
                        jay[J]=x_buffer[P+2];
                        jay[J+1]=x_buffer[P+1];
                        jay[J+2]=x_buffer[P];
                        }
                }
        }
        return 0;
}

int moon (int x,int y, int r,int day,int cres)
{

        float rads,dtheta,ftheta;
        int xp,yp,xoff,yoff,xm,ym,rrr,night;
	xoff=cres;yoff=-cres;
	xm=x-xoff;ym=y-yoff;
	rrr=(120*r*r)/100;
	night=300-day;

        dtheta=asin(1/(2*(float)r));

        //printf ("checking \n");
        for (ftheta=0;ftheta<2*M_PI;ftheta+=dtheta)
        {
                xp=x+(r*sin(ftheta));
                yp=y+(r*cos(ftheta));
                if (xp<0 || xp>=X_SIZE){ return 1; }
                if (yp<0 || yp>=Y_SIZE){ return 1; }
        }

        //printf ("checked \n");
        for (rads=r;rads>0.5;rads-=0.5)
        {
                dtheta=asin(1/(2*rads));
                for (ftheta=0;ftheta<2*M_PI;ftheta+=dtheta)
                {
                        int R,P,J;
                        float roff;
                        roff=1+(sin(ftheta*0));
                        roff=roff*3;
                        xp=x+((rads-roff)*sin(ftheta));
                        yp=y+(((rads-roff)*cos(ftheta)));
                        P=((xp*4)+(yp*XS));
                        J=((xp*3)+(yp*JS));

			R=((xp-xm)*(xp-xm))+((yp-ym)*(yp-ym));
			if ( R> rrr )
			{
                        x_buffer[P]=((bb[6]*(night))/300)+((day*mb)/300);
                        x_buffer[P+1]=((gg[6]*(night))/300)+((day*mg)/300);
                        x_buffer[P+2]=((rr[6]*(night))/300)+((day*mr)/300);
                        jay[J]=x_buffer[P+2];
                        jay[J+1]=x_buffer[P+1];
                        jay[J+2]=x_buffer[P];
			}
                }
        }
        return 0;
}


void clear (int day)
{
	int j,x,y;
	j=0;

	mr=DR-(((DR-NR)*day)/300);
	mg=DG-(((DG-NG)*day)/300);
	mb=DB-(((DB-NB)*day)/300);
        for (y=0;y<Y_SIZE;y++)
        {
             int Y;
             Y=y*X_SIZE*4;
             for (x=0;x<X_SIZE*4;x+=4)
             {

                     x_buffer[x+Y]=mb; x_buffer[x+Y+1]=mg; x_buffer[x+Y+2]=mr; jay[j++]=mr; jay[j++]=mg; jay[j++]=mb;
             }
        }
}

struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}

GLOBAL(int)
read_JPEG_file (char * filename, unsigned char * dots, int * params)
{
  /* This struct contains the JPEG decompression parameters and pointers to
   * working space (which is allocated as needed by the JPEG library).
   */
  struct jpeg_decompress_struct cinfo;
  /* We use our private extension JPEG error handler.
   * Note that this struct must live as long as the main JPEG parameter
   * struct, to avoid dangling-pointer problems.
   */
  struct my_error_mgr jerr;
  /* More stuff */
  FILE * infile;		/* source file */
  JSAMPARRAY buffer;		/* Output row buffer */
  int row_stride;		/* physical row width in output buffer */

  if ((infile = fopen(filename, "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
    return 0;
  }

  /* Step 1: allocate and initialize JPEG decompression object */

  /* We set up the normal JPEG error routines, then override error_exit. */
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  /* Establish the setjmp return context for my_error_exit to use. */
  if (setjmp(jerr.setjmp_buffer)) {
    /* If we get here, the JPEG code has signaled an error.
     * We need to clean up the JPEG object, close the input file, and return.
     */
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    return 0;
  }
  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress(&cinfo);

  /* Step 2: specify data source (eg, a file) */

  jpeg_stdio_src(&cinfo, infile);

  /* Step 3: read file parameters with jpeg_read_header() */

  (void) jpeg_read_header(&cinfo, TRUE);
  /* We can ignore the return value from jpeg_read_header since
   *   (a) suspension is not possible with the stdio data source, and
   *   (b) we passed TRUE to reject a tables-only JPEG file as an error.
   * See libjpeg.txt for more info.
   */

  /* Step 5: Start decompressor */

  (void) jpeg_start_decompress(&cinfo);
  /* We can ignore the return value since suspension is not possible
   * with the stdio data source.
   */

  /* We may need to do some setup of our own at this point before reading
   * the data.  After jpeg_start_decompress() we have the correct scaled
   * output image dimensions available, as well as the output colormap
   * if we asked for color quantization.
   * In this example, we need to make an output work buffer of the right size.
   */ 
  /* JSAMPLEs per row in output buffer */
  row_stride = cinfo.output_width * cinfo.output_components;
  /* Make a one-row-high sample array that will go away when done with image */
  buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);


  /* Step 6: while (scan lines remain to be read) */
  /*           jpeg_read_scanlines(...); */

  /* Here we use the library's state variable cinfo.output_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   */

  while (cinfo.output_scanline < cinfo.output_height) {
    /* jpeg_read_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could ask for
     * more than one scanline at a time if that's more convenient.
     */
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);
    memcpy (dots+(row_stride*cinfo.output_scanline),buffer[0],row_stride);
    /* Assume put_scanline_someplace wants a pointer and sample count. */
    /* put_scanline_someplace(buffer[0], row_stride); */

  }
  /* Step 7: Finish decompression */
  params[0]=cinfo.output_width;
  params[1]=cinfo.output_height;
  params[2]=cinfo.output_components;

  (void) jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(infile);

  /* And we're done! */
  return 1;
}

int jayit(unsigned char *screen,int image_width, int image_height, char *name)
{

int row_stride,ex,why,cmp,div,set;
unsigned char *image,**row_pointer,*cr,*cg,*cb;
row_pointer=(unsigned char **)malloc(1);

struct jpeg_compress_struct cinfo;
struct jpeg_error_mgr jerr;
FILE * outfile;		/* target file */
cinfo.err = jpeg_std_error(&jerr);
jpeg_create_compress(&cinfo);
if ((outfile = fopen(name, "wb")) == NULL) { 
	fprintf(stderr, "can't open file\n");
	exit(1);
}
jpeg_stdio_dest(&cinfo, outfile);
cinfo.image_width = image_width; 	/* image width and height, in pixels */
cinfo.image_height = image_height;
cinfo.input_components = 3;		/* # of color components per pixel */
cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
jpeg_set_defaults(&cinfo);
jpeg_set_quality(&cinfo,100,TRUE); /* limit to baseline-JPEG values */
jpeg_start_compress(&cinfo, TRUE);

  row_stride = image_width * 3;	/* JSAMPLEs per row in image_buffer */

  while (cinfo.next_scanline < cinfo.image_height) {
    /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
    row_pointer[0] = & screen[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
jpeg_finish_compress(&cinfo);
fclose(outfile);
jpeg_destroy_compress(&cinfo);
}

void init_x()
{
/* get the colors black and white (see section for details) */
        unsigned long black,white;

        x_buffer=(unsigned char *)malloc(sizeof(unsigned char)*4*X_SIZE*Y_SIZE);
        display=XOpenDisplay((char *)0);
        screen=DefaultScreen(display);
        black=BlackPixel(display,screen),
        white=WhitePixel(display,screen);
        win=XCreateSimpleWindow(display,DefaultRootWindow(display),0,0,
                X_SIZE, Y_SIZE, 5, white,black);
        XSetStandardProperties(display,win,"image","images",None,NULL,0,NULL);
        gc=XCreateGC(display, win, 0,0);
        XSetBackground(display,gc,black); XSetForeground(display,gc,white);
        XClearWindow(display, win);
        XMapRaised(display, win);
        //XMoveWindow(dis, win,window_x,100);
        Visual *visual=DefaultVisual(display, 0);
        x_image=XCreateImage(display, visual, DefaultDepth(display,DefaultScreen(display)), ZPixmap, 0, x_buffer, X_SIZE, Y_SIZE, 32, 0);
};

void close_x() {
        XFreeGC(display, gc);
        XDestroyWindow(display,win);
        XCloseDisplay(display);
        exit(1);
};

void redraw() {
        XClearWindow(display, win);
};


