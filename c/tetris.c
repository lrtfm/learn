/*
file:
	main.h

author:
	lrtfm <yzz1215@live.cn>
	lrtfm.github.com
date:	
	2012-03-03 21:15:42  

command:	
	gcc -g main.c  `pkg-config --cflags --libs gtk+-2.0`
*/

/*Windows
#pragma   comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
*/
#undef NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <assert.h>
#define Width 14
#define Height 25
#define Gap 20
#define Cube 10

#define Down 1
#define Left 2
#define Right 3
#define Rotate 0
#define GAME_ON 1
#define GAME_OFF 0
#define GAME_STOP 2
#define LEVEL4 30000
#define LEVEL3 15000
#define LEVEL2 8000 
#define LEVEL1 3000


int* rotate_curr_box();
void make_box();
static gboolean time_handler (GtkWidget *widget);



struct LINE{
	struct LINE *pre;
	int l[Width];
	int num;
	struct LINE *next;
}*header;

int Box[7][4][4]={
	{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
	{{0,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,0,0}},
	{{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
	{{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
	{{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
	{{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
	{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}}
};

gint timer;
int x = Width/2-2;
int y = -3;
int *Curr_Box=NULL;
int *Next_Box=NULL;
int game = GAME_OFF;
struct LINE *Curr_Line=NULL;

int Score=0;
int Level=0;

int Level_speed=500;


void free_space()
{
	struct LINE *p=NULL,*p2;
	int i=1;
	
	if (header->next==NULL){
		printf("there is no space to free\n");
		return;
	}
	p=header->next;
	while(p->next!=NULL){
		p2=p;
		p=p2->next;
		free(p2);
		//printf("free ok %d\n", i);
		i++;
	}
	free(p);
	header->next=NULL;
	header->pre=NULL;
	printf("space free ok\n");
}
	

void update_data(GtkWidget *widget)
{
	int i,j;
	int num = 0;
	
	struct LINE *temp = NULL;
	struct LINE *p1,*p2;
	temp = Curr_Line;
	for (i = 0; i < 4; i++){
		if ((y+i) < 0)continue;
		for (j = 0; j < 4; j++){
			if (((x + j) >= 0) && ((x + j) <= (Width-1)) &&Curr_Box[i*4+j]){
				Curr_Line->l[x+j] = Curr_Box[i*4+j];
				Curr_Line->num++;
				//printf("updata,num = %d; ", Curr_Line->num);
			}
		}
		//y++;
		//printf("\n");
		if (Curr_Line->next!=NULL)
			Curr_Line=Curr_Line->next;
		else break;
	}
	Curr_Line = temp;
	for (i = 0; i < 4; i++){
		//printf("y+i=%d\n",y+i);
		//printf("y+i=%d,num=%d\n",y+i,Curr_Line->num);
		if (Curr_Line==NULL)break;
		if ((y+i) < 0)continue;
		//printf("i = %d\n",i);
		if ((Curr_Line->next==NULL)&&(Curr_Line->num == Width)){
			p1 = Curr_Line->pre;
			p2 = header->next;
			header->next = Curr_Line;
			Curr_Line->next = p2;
			Curr_Line->pre = header;
			p2->pre = Curr_Line;
			p1->next = NULL;
			header->pre = p1;
			
			memset(Curr_Line->l,0,Width*sizeof(int));
			Curr_Line->num = 0;
			num++;
			break;
		}
		else if (Curr_Line->num >= Width){
			
			p1 = Curr_Line->pre;
			p2 = Curr_Line->next;
			p1->next = p2;
			p2->pre = p1;
			
			p1 = header->next;
			header->next = Curr_Line;
			Curr_Line->pre = header;
			Curr_Line->next = p1;
			p1->pre = Curr_Line;
			memset(Curr_Line->l,0,Width*sizeof(int));
			Curr_Line->num = 0;
			Curr_Line = p2;
			num++;
		}
		else if (Curr_Line->next==NULL)break;
		else {
			Curr_Line=Curr_Line->next;
		}		
	}
	
	switch (num){
		case 1:Score += 100;break;
		case 2:Score += 300;break;
		case 3:Score += 600;break;
		case 4:Score += 1000;break;
		default:break;	
	}
	Curr_Line=header->next;
	if (Score >= LEVEL4&&Level<4){
		Level = 4;
		gtk_timeout_remove(timer);
		timer = g_timeout_add(80, (GSourceFunc) time_handler, (gpointer) widget);
	}
	else if (Score >= LEVEL3&&Level<3){
		Level = 3;
		gtk_timeout_remove(timer);
		timer = g_timeout_add(120, (GSourceFunc) time_handler, (gpointer) widget);
	}
	else if (Score >= LEVEL2&&Level<2){
		Level = 2;
		gtk_timeout_remove(timer);
		timer = g_timeout_add(180, (GSourceFunc) time_handler, (gpointer) widget);
	}
	else if (Score >= LEVEL1&&Level<1){
		Level = 1;	
		gtk_timeout_remove(timer);
		timer = g_timeout_add(250, (GSourceFunc) time_handler, (gpointer) widget);
	}
	
}

void draw_data(cairo_t *cr)
{
	struct LINE *Line;
	Line = header;
	
	int i = Height;
	int j;
	for (i = 0; i < Height; i++){
		Line=Line->next;
		for (j = 0; j < Width; j++){
			//printf("j=%d\n,%o\n",j,Line->l);
			if (Line->l[j]){
				cairo_move_to(cr, j*Cube, i*Cube);

				cairo_rectangle(cr, 
						j*Cube, 
						i*Cube, 
						Cube, 
						Cube);
				cairo_set_source_rgb (cr, 0, 0, 1);
				cairo_fill_preserve (cr);
				cairo_set_source_rgb (cr, 0, 0, 0);
				cairo_stroke (cr);
			}
		}
	}
}



void init_game(struct LINE *p_header)
{

	game = GAME_ON;
	Score = 0;
	Curr_Box=NULL;
	Next_Box=NULL;
	int i = Height;
	
	make_box();
	p_header->next = NULL;
	p_header->pre = NULL;
	struct LINE *p = NULL ,*now = p_header;
	
	for ( ; i > 0; i--){
		if (!(now->next = (struct LINE*)malloc(sizeof(struct LINE)))){
			printf("Error:cannot malloc space\n");
			exit(1);
		}
		
		now->next->pre = now;
		now = now->next;
		now->next = NULL;
		
		memset(now->l,0,Width*sizeof(int));
		now->num = 0;
	}
	p_header->pre = now;
	Curr_Line = p_header->next;
	printf("malloc space OK\n");
	
		
}

int check_box(int state)
{
	int i,j;
	struct LINE *temp_Line=NULL;
	int *temp_box;
	int temp_x=x, temp_y=y;
	temp_Line=Curr_Line;
	switch (state){
		case Down:
			for (i = 0; i < 4; i++){
				temp_y++;
				if (temp_y<0) continue;
				if (temp_Line && temp_Line->next&&temp_y!=0)
					temp_Line=temp_Line->next;
				
				for (j = 0; j < 4; j++){
				
					assert(temp_Line!=NULL);
					
					
					if (((temp_x + j) < 0 || temp_y > (Height-1) || \
						(temp_x + j) > (Width-1) )&&	Curr_Box[i*4+j]){
						return 0;
					}
					else if((temp_x + j) < 0 || temp_y > (Height-1) \
						|| (temp_x + j) > (Width-1)){
						;
					}
					else if(temp_Line->l[temp_x+j]&& \
						Curr_Box[i*4+j])	
						return 0;	
				}
			}
			break;
		case Left:
		
			temp_x--;
			for (i = 0; i < 4; i++){
				/*if (temp_y<0){
					temp_y++;
					continue;
				}*/	
				for (j = 0; j < 4; j++){
					if (temp_y < 0 && ((temp_x + j)>=Width || temp_x +j <0)\
						&&Curr_Box[i*4+j]==1) return 0;
					else if (temp_y < 0)continue; 
				
				
					if (((temp_x + j) < 0 || temp_y > (Height-1) || \
						(temp_x + j) > (Width-1) )&&	Curr_Box[i*4+j])
						return 0;
					else if ((temp_x + j) < 0 || temp_y > (Height-1) \
						|| (temp_x + j) > (Width-1));
					else if (temp_Line->l[temp_x+j]&& \
						Curr_Box[i*4+j])
						return 0;
					
				}
				temp_y++;
				if (temp_Line && temp_Line->next)
					temp_Line=temp_Line->next;
			}
			break;
			
		case Right:
			temp_x++;
			for (i = 0; i < 4; i++){
				/*if (temp_y<0){
					temp_y++;
					continue;
				}*/		
				for (j = 0; j < 4; j++){
					if (temp_y < 0 && ((temp_x + j)>=Width || temp_x +j <0)\
						&&Curr_Box[i*4+j]==1) return 0;
					else if (temp_y < 0)continue; 
					
					if (((temp_x + j) < 0 || temp_y > (Height-1) || \
						(temp_x + j) > (Width-1) )&&	Curr_Box[i*4+j])
						return 0;
					else if((temp_x + j) < 0 || temp_y > (Height-1) \
						|| (temp_x + j) > (Width-1));
					else if(temp_Line->l[temp_x+j]&& \
						Curr_Box[i*4+j])
						return 0;
				}
				temp_y++;
				if (temp_Line && temp_Line->next)
					temp_Line=temp_Line->next;
			}
			break;
			
		case Rotate:
			temp_box = rotate_curr_box();
			for (i = 0; i < 4; i++){
				/*if (temp_y<0){
					temp_y++;
					continue;
				}*/		
				for (j = 0; j < 4; j++){
					if (temp_y < 0 && ((temp_x + j)>=Width || temp_x +j <0)\
						&&Curr_Box[i*4+j]==1) return 0;
					else if (temp_y < 0)continue; 
					
					if (((temp_x + j) < 0 || temp_y > (Height-1) || \
						(temp_x + j) > (Width-1) )&&	temp_box[i*4+j])
						return 0;
					else if((temp_x + j) < 0 || temp_y > (Height-1) \
						|| (temp_x + j) > (Width-1));
					else if(temp_Line->l[temp_x+j]&& \
						temp_box[i*4+j])
						return 0;
				}
				temp_y++;
				if (temp_Line && temp_Line->next)
					temp_Line=temp_Line->next;
			}
			free(temp_box);
			break;
		default : 
			break;
	}
	return 1;
}
	

void draw_box(cairo_t *cr,int *Box)
{
	int i = 0; 
	int j = 0;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			if (Box[4*i+j]==1){
				cairo_set_source_rgb (cr, 0, 0.3, 0.8);
				cairo_rectangle(cr, 
						(x+j)*Cube, 
						(y+i)*Cube, 
						Cube, 
						Cube);
				cairo_fill (cr);
			}
		}
	}	
}

void make_box()
{		
	time_t *tp=NULL;
	srand(time(tp));
	int n = rand()%7;
	int i = 0; 
	int j = 0;

	int *temp_box;
	
	
	
	if (Next_Box==NULL&&Curr_Box==NULL){
		Next_Box = (int *)malloc(16*sizeof(int));
		Curr_Box = (int *)malloc(16*sizeof(int));
		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){
				Curr_Box[4*i+j]=Box[n][i][j];
			}
		}
	}
	else {
		temp_box=Curr_Box;
		Curr_Box = Next_Box;
		Next_Box = temp_box;
	}

	n = rand()%7;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			Next_Box[4*i+j]=Box[n][i][j];
		}
	}
	
}


int* rotate_curr_box()
{
	int *temp_box;
	temp_box = (int *)malloc(16*sizeof(int));
	int i = 0; 
	int j = 0;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			temp_box[4*i+j]=Curr_Box[(3-j)*4+i];
		}
	}
	return temp_box;
}
	
	
	
void move_handler(GtkWidget *widget, GdkEventKey *event, gpointer data)
{

	
	if (event->keyval==GDK_space){
		if (game == GAME_ON)game = GAME_STOP;
		else if (game == GAME_STOP)game = GAME_ON;
		return;
	}
	
	if (game == GAME_OFF || game == GAME_STOP)return;
	int *temp_box;
	
	switch(event->keyval) {
		case GDK_Up:
			if (check_box(Rotate)){
				temp_box = rotate_curr_box();
				free(Curr_Box);
				Curr_Box = temp_box;
			}	
			break;
		case GDK_Left:
			x = x - check_box(Left);
			break;
		case GDK_Right:
			x = x + check_box(Right);
			break;
		case GDK_Down:
        		if (check_box(Down)){
        			y++;
        			//printf("y=%d\n",y);
        			if(y>0)
        				Curr_Line=Curr_Line->next;
        		}
        		else if(y<0){
				printf("Game Over\n");
				free_space();
				game = GAME_OFF;
			}
        		break;
        	default:break;
        }
        gtk_widget_queue_draw(widget);
}

void draw_over(cairo_t *cr)
{
	cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (cr, 18.0);


	cairo_move_to (cr, 10, Height*10/3);
	cairo_text_path (cr, "GAME OVER");

	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_set_line_width (cr, 1.56);
	cairo_stroke (cr);


}
void expose_handler(GtkWidget *widget, gpointer data)
{
	cairo_t *cr;
	
	cr = gdk_cairo_create(widget->window);
	
	
	cairo_set_source_rgb (cr, 1, 0.3, 0);
	cairo_rectangle (cr, 0, 0, Width*Cube, Height*Cube);
	cairo_fill(cr);
	if (game == GAME_ON){
		draw_data(cr);
		draw_box(cr,Curr_Box);
	}
	else {
		draw_over(cr);
	}
	cairo_destroy(cr);
}

static gboolean time_handler (GtkWidget *widget)
{
	if (game == GAME_STOP)return TRUE;
	if (game==GAME_ON){
		if( check_box(Down)){
			y++;
			if(y>0)
				Curr_Line=Curr_Line->next;
		}
		else if((!check_box(Down))&&y<0){
			printf("Game Over\n");
			free_space();
			game = GAME_OFF;
		}
		else {
			update_data(widget);
			gtk_widget_queue_draw(widget);
			y = -3;
			x = Width/2-2;
			Curr_Line=header->next;
			make_box();
		}
	}
	gtk_widget_queue_draw(widget);
	return TRUE;
}
void score_print(GtkWidget *widget)
{
	gchar str[50];

	sprintf(str, "Score:\n\t%d\nlevel:\n\t%d\t\t", Score, Level);

	gtk_label_set_text((GtkLabel*) widget,str);
	//gtk_widget_show(widget);
}
void next_box_print(GtkWidget *widget, gpointer data)
{
	cairo_t *cr;
	int i,j;
	cr = gdk_cairo_create(widget->window);
	//printf("draw next_box");
	
	cairo_set_source_rgb (cr, 1, 0.3, 0);
	cairo_rectangle (cr, 0, 0, 6*Cube, 6*Cube);
	cairo_fill(cr);
	
	if (game==GAME_ON){
		//printf("draw next_box,%d,%d\n",Next_Box[6],Next_Box[5]);
		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){
				if (Next_Box[4*i+j]==1){
					cairo_set_source_rgb (cr, 0, 0.3, 0.8);
					cairo_rectangle(cr, 
						(1+j)*Cube, 
						(1+i)*Cube, 
						Cube, 
						Cube);
					cairo_fill (cr);
				}
			}
		}
	}
	
	cairo_destroy(cr);
}
int main(int argc, char **argv)
{
	GtkWidget *window;
	GtkWidget *main_area;
	GtkWidget *fixed;
	GtkWidget *score_frame;
	GtkWidget *score_label;
	GtkWidget *next_box_area;
	
	struct LINE head ;
	header = &head;
	init_game(header);
	gtk_init(&argc, &argv);
	
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if (!window){
		g_print("Could not creat gtk+-window!\n");
		return 2;
	}
	gtk_widget_set_size_request(window, 2*Width*Cube+20, Height*Cube+40);
	
	g_signal_connect(G_OBJECT(window), 
			"destroy", 
			G_CALLBACK(gtk_main_quit), 
			NULL);
	
	
	main_area = gtk_drawing_area_new();
	if (!main_area){
		g_print("could not creat drawing-area!\n");
		return 3;
	}
	gtk_widget_set_size_request(main_area, Width*Cube, Height*Cube);
	
	next_box_area = gtk_drawing_area_new();
	if (!next_box_area){
		g_print("could not creat drawing-area!\n");
		return 3;
	}
	gtk_widget_set_size_request(next_box_area, 6*Cube, 6*Cube);
	
	
	
	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);
	
	
	gtk_fixed_put(GTK_FIXED(fixed), next_box_area,Width*Cube+60,50);
	
	gtk_fixed_put(GTK_FIXED(fixed), main_area, 20, 20);
	/*g_signal_connect_after(G_OBJECT(main_area), 
				"realize", 
				G_CALLBACK(realize_handler), 
				NULL);*/
	g_signal_connect(G_OBJECT(next_box_area), 
			"expose-event", 
			G_CALLBACK(next_box_print), 
			NULL);			
	g_signal_connect(G_OBJECT(main_area), 
			"expose-event", 
			G_CALLBACK(expose_handler), 
			NULL);
						
	g_signal_connect(G_OBJECT(window), 
			"key-press-event", 
			G_CALLBACK(move_handler), 
			NULL);
	
	score_frame=gtk_frame_new(NULL);
	score_label=gtk_label_new("Score:\n\t0\t\nlevel:\n\t0\t");
	gtk_container_add(GTK_CONTAINER(score_frame),score_label);
	gtk_fixed_put(GTK_FIXED(fixed), score_frame, Width*Cube+50, Height/2*Cube+10);				
			
				
				
	//gtk_widget_set_app_paintable(main_area, TRUE);
	//gtk_widget_show(main_area);
	//gtk_widget_show(window);
	gtk_widget_show_all(window);
	timer = g_timeout_add(400, (GSourceFunc) time_handler, (gpointer) window);
	g_timeout_add(100, (GSourceFunc) score_print, (gpointer) score_label);
	gtk_main();
	free_space();
	//释放空间
	return 0;
}
	
	
