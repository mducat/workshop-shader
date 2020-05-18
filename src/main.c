/*
** EPITECH PROJECT, 2019
** workshop
** File description:
** main
*/

#include <strings.h>
#include <stdlib.h>
#include <err.h>

#include <SFML/Graphics.h>

#include "shader.h"

int init_shader(shader_t *sh, int ac, char **av)
{
    sh->mode = (sfVideoMode) {800, 600, 32};
    sh->shader = sfShader_createFromFile(
        "assets/shader.vert", 0, "assets/shader.frag");
    sh->state = malloc(sizeof(sfRenderStates));
    sh->tex = sfTexture_create(sh->mode.width, sh->mode.height);
    sh->sampler = sfTexture_createFromFile("assets/texture.png", NULL);
    sh->sprite = sfSprite_create();
    sh->clock = sfClock_create();
    if (!sh->state || !sh->tex || !sh->sprite || !sh->clock || !sh->sampler)
        return (1);
    sh->state->blendMode = sfBlendAlpha;
    sh->state->shader = sh->shader;
    sh->state->transform = sfTransform_Identity;
    sh->state->texture = NULL;
    sfSprite_setTexture(sh->sprite, sh->tex, sfTrue);
    return (!sh->shader);
}

void handle_event(sfRenderWindow *win, sfEvent *ev, shader_t *sh)
{
    if (ev->type == sfEvtClosed)
        sfRenderWindow_close(win);
    if (ev->type == sfEvtMouseMoved)
        sfShader_setVec2Uniform(sh->shader, "u_mouse",
            (sfGlslVec2) {ev->mouseMove.x, ev->mouseMove.y});
}

void main_loop(sfRenderWindow *win, shader_t *sh)
{
    sfTime time = sfClock_getElapsedTime(sh->clock);
    double delta = (double) sfTime_asMilliseconds(time) / 1000;

    sfShader_setFloatUniform(sh->shader, "u_time", delta);
    sfRenderWindow_clear(win, sfBlack);
    sfRenderWindow_drawSprite(win, sh->sprite, sh->state);
    sfRenderWindow_display(win);
}

void free_shader(shader_t *sh)
{
    sfSprite_destroy(sh->sprite);
    sfShader_destroy(sh->shader);
    sfTexture_destroy(sh->tex);
    sfTexture_destroy(sh->sampler);
    free(sh->state);
}

int main(int ac, char **av)
{
    sfRenderWindow *window;
    sfEvent event;
    shader_t sh;

    if (init_shader(&sh, ac, av))
        errx(84, "Could not load shader assets !");
    sfShader_setVec2Uniform(sh.shader, "u_res",
        (sfGlslVec2) {sh.mode.width, sh.mode.height});
    sfShader_setTextureUniform(sh.shader, "u_tex", sh.sampler);
    window = sfRenderWindow_create(sh.mode, "My shader", sfClose, 0);
    sfRenderWindow_setFramerateLimit(window, 60);
    while (sfRenderWindow_isOpen(window)){
        while (sfRenderWindow_pollEvent(window, &event))
            handle_event(window, &event, &sh);
        main_loop(window, &sh);
    }
    free_shader(&sh);
    sfRenderWindow_destroy(window);
    return (0);
}
