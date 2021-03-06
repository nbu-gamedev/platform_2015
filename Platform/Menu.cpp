#include "Menu.h"
#include<iostream>

SDL_Texture* Menu::menu_closed = NULL;
SDL_Texture* Menu::menu_opened = NULL;
SDL_Texture* Menu::page_about = NULL;
SDL_Texture* Menu::page_controls = NULL;
SDL_Texture* Menu::btns_images[7][2] = {};

Menu::Menu()
{
    // position of menu
    pos.w = MENU_SIZE_W;
    pos.h = MENU_L_SIZE_H;
    pos.y = real_y = M_WINDOW_HEIGHT - MENU_L_SIZE_H;
    pos.x = (M_WINDOW_WIDTH - MENU_SIZE_W)/2;
    // position of controls/about page when opened
    page_c_pos.w = PAGE_CNTRLS_SIZE_W;
    page_c_pos.h = PAGE_CNTRLS_SIZE_H;
    page_c_pos.y = (M_WINDOW_HEIGHT - PAGE_CNTRLS_SIZE_H)/2;
    page_c_pos.x = (M_WINDOW_WIDTH - PAGE_CNTRLS_SIZE_W)/2;
    page_a_pos.w = PAGE_ABOUT_SIZE_W;
    page_a_pos.h = PAGE_ABOUT_SIZE_H;
    page_a_pos.y = (M_WINDOW_HEIGHT - PAGE_ABOUT_SIZE_H)/2;
    page_a_pos.x = (M_WINDOW_WIDTH - PAGE_ABOUT_SIZE_W)/2;
    menu = true;
    animation = false;
    page_open = false;
    direction = 1;

    children[0] = new Button(0,0);
    children[1] = new Button(0,1);
    for(int i = 2; i < 8; i++)
    {
        children[i] = new Button(1,i);
    }
}
Menu::~Menu()
{
    for(int i = 0; i < 8; i++)
    {
        delete children[i];
    }
}

void Menu::render_menu(SDL_Renderer * renderer)
{
    if (page_open)
    {
        //controls (button 2) or about (button 4) is selected
        if (children[2]->selected)
        {
            SDL_RenderCopy(renderer,  page_controls, NULL, &page_c_pos);
            children[6] -> render(renderer);
        }
        else
        {
            SDL_RenderCopy(renderer, page_about , NULL, &page_a_pos);
            children[7] -> render(renderer);
        }
    }
    else
    {
        SDL_RenderCopy(renderer, menu ? menu_opened : menu_closed, NULL, &pos);

        if(menu)
        {
            for(int i = 1; i < 6; i++)
            {
               children[i] -> render(renderer);
            }
        }
        else
        {
            children[0] -> render(renderer);
        }
    }
}

void Menu::update(int time, Mouse_event* me)
{
    if (animation)
    {
        double moved = time*animation_speed / 1000.;
        real_y += (-direction)*moved;
        pos.y = real_y;

        if ( pos.y > M_WINDOW_HEIGHT)
        {
            menu = !menu;
            direction *= -1;
            pos.h = menu ? MENU_L_SIZE_H : MENU_S_SIZE_H;
        }
         else if(real_y <  M_WINDOW_HEIGHT - pos.h)
        {
            pos.y = real_y = M_WINDOW_HEIGHT - pos.h;
            animation = false;
        }

        if(menu)
        {
            for(int i = 1; i < 6; i++)
            {
               children[i] -> pos.y = pos.y + relative_y[i];
            }
        }
        else
        {
            children[0] -> pos.y = pos.y + relative_y[0];
        }
    }
    else if (me)
    {
        if (page_open)
        {
            Button* active = children[2]->selected ? children[6] : children[7];
            if ( active -> update(me->x, me->y) && me->clicked)
            {
                page_open = false;
                //controls (button 2) or about (button 4) is selected
                children[2] -> selected = children[4] -> selected =  active -> selected = false;
            }
        }
        else
        {
            if(menu)
            {
                for(int i = 1; i < 6; i++)
                {
                    if ( children[i] -> update(me->x, me->y) && me->clicked)
                    {
                        switch(i)
                        {
                            case 1: toggle_menu(); children[1] -> selected = false; break;
                            case 2: case 4: page_open = true; break;// controls/about page is opened
                            case 3: MUSIC = !MUSIC; break;
                            case 5: GAME_RUNNING = false; break;
                            default:break;

                        }
                    break;
                   }
                }
            }
            else
            {
                if ( children[0] -> update(me->x, me->y) && me->clicked)
                {
                    toggle_menu();
                    children[0] -> selected = false;
                }
            }
        }
    }
}

void Menu::toggle_menu()
{
    animation = true;
    direction *= -1;
}

bool point_inside_tr(int p[3][2], int x, int y){
    int a = (x-p[0][0])*(p[1][1] - p[0][1]) - (p[1][0] - p[0][0])*(y-p[0][1]);
    int b = (x-p[1][0])*(p[2][1] - p[1][1]) - (p[2][0] - p[1][0])*(y-p[1][1]);
    int c = (x-p[2][0])*(p[0][1] - p[2][1]) - (p[0][0] - p[2][0])*(y-p[2][1]);

    return ((a < 0 && b < 0 && c < 0) || (a > 0 && b > 0 && c > 0));
}

bool point_inside_rec(int p[3][2], int x, int y){

    return (x > p[0][0] && x < p[1][0] && y > p[0][1] && y < p[1][1]);
}

Button::Button(int tp, int number)
{
    type = tp;
    num = number;
    selected = false;
    //init collision points and position on the screen
    if(num == 0)
    {
        points[0][0] = (M_WINDOW_WIDTH)/2;
        points[0][1] = relative_y[0] + M_WINDOW_HEIGHT - MENU_S_SIZE_H;
        points[1][0] = (M_WINDOW_WIDTH - btns_sizes[0][0])/2;
        points[1][1] = relative_y[0] + btns_sizes[0][1] + M_WINDOW_HEIGHT - MENU_S_SIZE_H;
        points[2][0] = (M_WINDOW_WIDTH + btns_sizes[0][0])/2;
        points[2][1] = relative_y[0] + btns_sizes[0][1] + M_WINDOW_HEIGHT - MENU_S_SIZE_H;

        pos.x = points[1][0];
        pos.y = points[0][1];
    }
    else if (num == 1)
    {
        points[0][0] = (M_WINDOW_WIDTH - btns_sizes[1][0])/2;
        points[0][1] = relative_y[1] + M_WINDOW_HEIGHT - MENU_L_SIZE_H;
        points[1][0] = (M_WINDOW_WIDTH + btns_sizes[1][0])/2;
        points[1][1] = relative_y[1] + M_WINDOW_HEIGHT - MENU_L_SIZE_H;
        points[2][0] = (M_WINDOW_WIDTH)/2;
        points[2][1] = relative_y[1] + btns_sizes[1][1]  + M_WINDOW_HEIGHT - MENU_L_SIZE_H;

        pos.x = points[0][0];
        pos.y = points[0][1];
    }
    else if (num == 6)
    {
        points[0][0] = 500*SCALE_FACTOR + (M_WINDOW_WIDTH - PAGE_CNTRLS_SIZE_W)/2;
        points[0][1] = 418*SCALE_FACTOR + (M_WINDOW_HEIGHT - PAGE_CNTRLS_SIZE_H)/2;
        points[1][0] = points[0][0] + btns_sizes[6][0];
        points[1][1] = points[0][1] + btns_sizes[6][1];

        pos.x = points[0][0];
        pos.y = points[0][1];
    }
    else if (num == 7) // TO UPDATE
    {
        num = 6; // it's an OK button too, but with different position
        points[0][0] = 748*SCALE_FACTOR + (M_WINDOW_WIDTH - PAGE_ABOUT_SIZE_W)/2;
        points[0][1] = 587*SCALE_FACTOR + (M_WINDOW_HEIGHT - PAGE_ABOUT_SIZE_H)/2;
        points[1][0] = points[0][0] + btns_sizes[6][0];
        points[1][1] = points[0][1] + btns_sizes[6][1];

        pos.x = points[0][0];
        pos.y = points[0][1];
    }
    else
    {
        points[0][0] = (M_WINDOW_WIDTH - btns_sizes[num][0])/2;
        points[0][1] = relative_y[num] + M_WINDOW_HEIGHT - MENU_L_SIZE_H;
        points[1][0] = (M_WINDOW_WIDTH + btns_sizes[num][0])/2;
        points[1][1] = relative_y[num] + btns_sizes[num][1] + M_WINDOW_HEIGHT - MENU_L_SIZE_H;
        points[2][0] = points[2][1] = 0;

        pos.x = points[0][0];
        pos.y = points[0][1];
    }
    pos.w = btns_sizes[num][0];
    pos.h = btns_sizes[num][1];
}
bool Button::update(int x, int y)
{
    if (type == 0)
    {
        selected = point_inside_tr(points, x, y);
    }
    else
    {
        selected = point_inside_rec(points, x, y);
    }

    return selected;
}
void Button::render(SDL_Renderer * renderer)
{
    SDL_RenderCopy(renderer, selected ? Menu::btns_images[num][1] : Menu::btns_images[num][0], NULL, &pos);
}
