/*
********************************************************************************
Vectron - map editor for Armagetron Advanced.
Copyright (C) 2014 	Tristan Whitcher 	(tristan.whitcher@gmail.com)
David Dubois 		(ddubois@jotunstudios.com)
********************************************************************************

This file is part of Vectron.

Vectron is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Vectron is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Vectron.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Shader.h"

Shader::Shader( string vertName, string fragName ) {
    load( vertName, fragName );
}

void Shader::bind() {
    glUseProgram( glName );
    glEnableVertexAttribArray( verts );
}

void Shader::setMVP( glm::mat4 &MVPmat ) {
    glUniformMatrix4fv( MVPloc, 1, GL_FALSE, &MVPmat[0][0] );
}

//mostly from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/#Shader_Compilation
void Shader::load( string vertName, string fragName ) {
    // Create the shaders
    GLuint VertexShaderID = glCreateShader( GL_VERTEX_SHADER );
    GLuint FragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );

    // Read the Vertex Shader code from the file
    string VertexShaderCode;
    ifstream VertexShaderStream( vertName.c_str(), ios::in );
    if( VertexShaderStream.is_open() ) {
        string Line = "";
        while( getline( VertexShaderStream, Line ) )
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    } else {
        cout << "ERROR: Cannot open " << vertName << "\n";
    }

    // Read the Fragment Shader code from the file
    string FragmentShaderCode;
    ifstream FragmentShaderStream( fragName.c_str(), ios::in );
    if( FragmentShaderStream.is_open() ) {
        string Line = "";
        while( getline( FragmentShaderStream, Line ) )
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    cout << "Compiling shader : " << vertName <<"\n";
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource( VertexShaderID, 1, &VertexSourcePointer, NULL );
    glCompileShader( VertexShaderID );

    // Check Vertex Shader
    glGetShaderiv( VertexShaderID, GL_COMPILE_STATUS, &Result );
    glGetShaderiv( VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength );
    vector<char> VertexShaderErrorMessage( InfoLogLength );
    glGetShaderInfoLog( VertexShaderID, InfoLogLength, NULL,
        &VertexShaderErrorMessage[0] );
    cout << &VertexShaderErrorMessage[0] << "\n";

    // Compile Fragment Shader
    cout << "Compiling shader : " << fragName <<"\n";
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource( FragmentShaderID, 1, &FragmentSourcePointer, NULL );
    glCompileShader( FragmentShaderID );

    // Check Fragment Shader
    glGetShaderiv( FragmentShaderID, GL_COMPILE_STATUS, &Result );
    glGetShaderiv( FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength );
    vector<char> FragmentShaderErrorMessage( InfoLogLength );
    glGetShaderInfoLog( FragmentShaderID, InfoLogLength, NULL,
        &FragmentShaderErrorMessage[0] );
    cout << &FragmentShaderErrorMessage[0] << "\n";

    // Link the program
    cout<< "Linking program\n";
    glName = glCreateProgram();
    glAttachShader( glName, VertexShaderID );
    glAttachShader( glName, FragmentShaderID );
    glLinkProgram( glName );

    // Check the program
    glGetProgramiv( glName, GL_LINK_STATUS, &Result );
    glGetProgramiv( glName, GL_INFO_LOG_LENGTH, &InfoLogLength );
    vector<char> ProgramErrorMessage( max( InfoLogLength, int( 1 ) ) );
    glGetProgramInfoLog( glName, InfoLogLength, NULL,
        &ProgramErrorMessage[0] );
    cout << &ProgramErrorMessage[0] <<"\n";

    glDeleteShader( VertexShaderID );
    glDeleteShader( FragmentShaderID );

    verts = glGetAttribLocation( glName, "verts" );
    MVPloc = glGetUniformLocation( glName, "MVP" );
}