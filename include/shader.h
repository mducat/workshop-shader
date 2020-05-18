/*
** EPITECH PROJECT, 2020
** workshop
** File description:
** header file
*/

#ifndef _SH_H
#define _SH_H

typedef struct shader {
    sfVideoMode mode;
    sfShader *shader;
    sfRenderStates *state;
    sfTexture *tex;
    sfTexture *sampler;
    sfSprite *sprite;
    sfClock *clock;
} shader_t;

#endif
