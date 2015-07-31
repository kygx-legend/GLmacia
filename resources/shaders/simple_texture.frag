precision mediump float;
uniform sampler2D uSampler;
varying vec2 texCoord;
void main() {
    gl_FragColor = texture2D(uSampler, texCoord);
}
