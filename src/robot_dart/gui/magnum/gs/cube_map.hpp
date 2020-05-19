#ifndef ROBOT_DART_GUI_MAGNUM_GS_CUBE_MAP_HPP
#define ROBOT_DART_GUI_MAGNUM_GS_CUBE_MAP_HPP

#include <robot_dart/gui/magnum/gs/material.hpp>

#include <Corrade/Containers/ArrayView.h>
#include <Corrade/Containers/Reference.h>
#include <Corrade/Utility/Assert.h>

#include <Magnum/GL/AbstractShaderProgram.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Shaders/Generic.h>

namespace robot_dart {
    namespace gui {
        namespace magnum {
            namespace gs {
                class CubeMap : public Magnum::GL::AbstractShaderProgram {
                public:
                    using Position = Magnum::Shaders::Generic3D::Position;
                    using TextureCoordinates = Magnum::Shaders::Generic3D::TextureCoordinates;

                    enum class Flag : Magnum::UnsignedByte {
                        DiffuseTexture = 1 << 0, /**< The shader uses diffuse texture instead of color */
                    };

                    using Flags = Magnum::Containers::EnumSet<Flag>;

                    explicit CubeMap(Flags flags = {});
                    explicit CubeMap(Magnum::NoCreateT) noexcept;

                    Flags flags() const;

                    CubeMap& set_transformation_matrix(const Magnum::Matrix4& matrix);
                    CubeMap& set_shadow_matrices(Magnum::Matrix4 matrices[6]);
                    CubeMap& set_light_position(const Magnum::Vector3& position);
                    CubeMap& set_far_plane(Magnum::Float far_plane);
                    CubeMap& set_light_index(Magnum::Int index);
                    CubeMap& set_material(Material& material);

                private:
                    Flags _flags;
                    Magnum::Int _transformation_matrix_uniform{0},
                        _shadow_matrices_uniform{5},
                        _light_position_uniform{1},
                        _far_plane_uniform{2},
                        _light_index_uniform{3},
                        _diffuse_color_uniform{4};
                };

                CORRADE_ENUMSET_OPERATORS(CubeMap::Flags)
            } // namespace gs
        } // namespace magnum
    } // namespace gui
} // namespace robot_dart

#endif