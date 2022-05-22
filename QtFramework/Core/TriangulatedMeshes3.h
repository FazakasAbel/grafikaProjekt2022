#pragma once

#include "DCoordinates3.h"
#include <GL/glew.h>
#include <iostream>
#include <string>
#include "TriangularFaces.h"
#include "TCoordinates4.h"
#include <vector>

namespace cagd
{
    class TriangulatedMesh3
    {
        friend class ParametricSurface3;
        friend class TensorProductSurface3;

        // homework: output to stream:
        // vertex count, face count
        // list of vertices
        // list of unit normal vectors
        // list of texture coordinates
        // list of faces
        friend std::ostream& operator <<(std::ostream& lhs, const TriangulatedMesh3& rhs);

        // homework: input from stream: inverse of the ostream operator
        friend std::istream& operator >>(std::istream& lhs, TriangulatedMesh3& rhs);

    protected:
        // vertex buffer object identifiers
        GLenum                      _usage_flag;
        GLuint                      _vbo_vertices;
        GLuint                      _vbo_normals;
        GLuint                      _vbo_tex_coordinates;
        GLuint                      _vbo_indices;

        // corners of bounding box
        DCoordinate3                 _leftmost_vertex;
        DCoordinate3                 _rightmost_vertex;

        // geometry
        std::vector<DCoordinate3>    _vertex;
        std::vector<DCoordinate3>    _normal;
        std::vector<TCoordinate4>    _tex;
        std::vector<TriangularFace>  _face;

    public:
        // special and default constructor
        TriangulatedMesh3(GLuint vertex_count = 0, GLuint face_count = 0, GLenum usage_flag = GL_STATIC_DRAW);

        // copy constructor
        TriangulatedMesh3(const TriangulatedMesh3& mesh);

        // assignment operator
        TriangulatedMesh3& operator =(const TriangulatedMesh3& rhs);

        // deletes all vertex buffer objects
        GLvoid DeleteVertexBufferObjects();

        // renders the geometry
        GLboolean Render(GLenum render_mode = GL_TRIANGLES) const;

        // updates all vertex buffer objects
        GLboolean UpdateVertexBufferObjects(GLenum usage_flag = GL_STATIC_DRAW);

        // loads the geometry (i.e. the array of vertices and faces) stored in an OFF file
        // at the same time calculates the unit normal vectors associated with vertices
        GLboolean LoadFromOFF(const std::string& file_name, GLboolean translate_and_scale_to_unit_cube = GL_FALSE);

        // homework: saves the geometry into an OFF file
        GLboolean SaveToOFF(const std::string& file_name) const;

        // mapping vertex buffer objects
        GLfloat* MapVertexBuffer(GLenum access_flag = GL_READ_ONLY) const;
        GLfloat* MapNormalBuffer(GLenum access_flag = GL_READ_ONLY) const;  // homework
        GLfloat* MapTextureBuffer(GLenum access_flag = GL_READ_ONLY) const; // homework

        // unmapping vertex buffer objects
        GLvoid UnmapVertexBuffer() const;
        GLvoid UnmapNormalBuffer() const;   // homework
        GLvoid UnmapTextureBuffer() const;  // homework

        // get properties of geometry
        size_t VertexCount() const; // homework
        size_t FaceCount() const;   // homework

        // destructor
        virtual ~TriangulatedMesh3();
    };

    inline std::ostream& operator <<(std::ostream& lhs, const TriangulatedMesh3& rhs)
    {
        GLuint vcount = rhs.VertexCount();
        GLuint fcount = rhs.FaceCount();
        lhs << vcount << " " << fcount << std::endl;

        for(std::vector<DCoordinate3>::const_iterator it = rhs._vertex.begin(); it != rhs._vertex.end(); it++)
        {
            lhs << &it << " ";
        }

        for(std::vector<DCoordinate3>::const_iterator it = rhs._normal.begin(); it != rhs._normal.end(); it++)
        {
            lhs << &it << " ";
        }

        for(std::vector<TCoordinate4>::const_iterator it = rhs._tex.begin(); it != rhs._tex.end(); it++)
        {
            lhs << &it << " ";
        }

        for(std::vector<TriangularFace>::const_iterator it = rhs._face.begin(); it != rhs._face.end(); it++)
        {
            lhs << &it << " ";
        }

        return lhs;
    }

    inline std::istream& operator >>(std::istream& lhs, TriangulatedMesh3& rhs)
    {
        rhs.DeleteVertexBufferObjects();

        GLuint vcount;
        GLuint fcount;
        lhs >> vcount >> fcount;

        lhs >> rhs._leftmost_vertex;
        lhs >> rhs._rightmost_vertex;

        rhs._vertex.resize(vcount);
        rhs._face.resize(fcount);
        rhs._normal.resize(vcount);
        rhs._tex.resize(vcount);

        for(std::vector<DCoordinate3>::iterator it = rhs._vertex.begin(); it != rhs._vertex.end(); it++)
        {
            lhs >> *it;
        }


        for(std::vector<DCoordinate3>::iterator it = rhs._normal.begin(); it != rhs._normal.end(); it++)
        {
            lhs >> *it;
        }

        for(std::vector<TCoordinate4>::iterator it = rhs._tex.begin(); it != rhs._tex.end(); it++)
        {
            lhs >> *it;
        }

        for(std::vector<TriangularFace>::iterator it = rhs._face.begin(); it != rhs._face.end(); it++)
        {
            lhs >> *it;
        }

        rhs.UpdateVertexBufferObjects();

        return lhs;
    }
}
