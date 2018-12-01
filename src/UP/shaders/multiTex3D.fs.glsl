#version 330

// Entrées du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform sampler2D uTexture_diffuse1;
uniform sampler2D uTexture_specular1;

void main() {
  vec3 tx1 = texture(uTexture_diffuse1, vTexCoords).xyz;
  vec3 tx2 = texture(uTexture_specular1, vTexCoords).xyz;
  fFragColor = tx1+tx2;
}
