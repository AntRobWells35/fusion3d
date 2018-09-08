#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inCol;
layout(location = 2) in vec3 inUV0;
layout(location = 3) in vec3 inUV1;
layout(location = 4) in vec3 inNorm;
layout(location = 5) in vec3 inBinorm;
layout(location = 6) in vec3 inTangent;

layout(location = 0) out vec3 fragColor;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    gl_Position = vec4(inPos, 1.0);
    fragColor = inCol;
}