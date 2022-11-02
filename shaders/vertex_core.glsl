/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_core.glsl                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: difool <eric.cantelpi@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:00:23 by difool            #+#    #+#             */
/*   Updated: 2022/06/14 17:34:15 by difool           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
