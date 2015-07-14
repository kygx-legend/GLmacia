// points.
var g_points = [
    0.0, 1.0,                  // a.
    -Math.sqrt(3.0) / 2.0, -0.5,  // b.
    Math.sqrt(3.0) / 2.0, -0.5,   // c.
];

// reset function.
function reset(gl, u_matrix) {
  // unit matrix to reset.
  var matrix = [
      1.0, 0.0, 0.0, 0.0,
      0.0, 1.0, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      0.0, 0.0, 0.0, 1.0,
  ];

  gl.uniformMatrix4fv(u_matrix, false, new Float32Array(matrix));

  clearBuffer(gl);

  gl.drawArrays(gl.TRIANGLES, 0, g_points.length / 2);
}

// translate function.
function translate(gl, u_matrix, x, y) {
  // translate matrix.
  var matrix = [
      1.0, 0.0, 0.0, 0.0,
      0.0, 1.0, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      x, y, 0.0, 1.0,
  ];

  gl.uniformMatrix4fv(u_matrix, false, new Float32Array(matrix));

  clearBuffer(gl);

  gl.drawArrays(gl.TRIANGLES, 0, g_points.length / 2);
}

// scale function.
function scale(gl, u_matrix, x, y) {
  // scale matrix.
  var matrix = [
      x, 0.0, 0.0, 0.0,
      0.0, y, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      0.0, 0.0, 0.0, 1.0,
  ];

  gl.uniformMatrix4fv(u_matrix, false, new Float32Array(matrix));

  clearBuffer(gl);

  gl.drawArrays(gl.TRIANGLES, 0, g_points.length / 2);
}

// rotate function.
function rotate(gl, u_matrix, angle) {
  var radian = Math.PI * parseFloat(angle) / 180.0;
  var sin = Math.sin(radian);
  var cos = Math.cos(radian);
  
  // rotate matrix.
  var matrix = [
      cos, sin, 0.0, 0.0,
      -sin, cos, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      0.0, 0.0, 0.0, 1.0,
  ];

  gl.uniformMatrix4fv(u_matrix, false, new Float32Array(matrix));

  clearBuffer(gl);

  gl.drawArrays(gl.TRIANGLES, 0, g_points.length / 2);
}

// main function.
function main() {
  var VSHADER_SOURCE =
      'attribute vec4 a_Position;\n' +
      'uniform mat4 u_Matrix;\n' +
      'void main() {\n' +
      '  gl_Position = u_Matrix * a_Position;\n' +
      '}\n';
  var FSHADER_SOURCE =
      'precision mediump float;\n' +
      'uniform vec4 u_FragColor;\n' +
      'void main() {\n' +
      '  gl_FragColor = u_FragColor;\n' +
      '}\n';

  var canvas = document.getElementById("webgl");
  var gl = getWebGLContext(canvas);

  if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
    alert("Fail to initialize shaders!");
    return;
  }

  // get attributes.
  var a_position = gl.getAttribLocation(gl.program, 'a_Position');
  checkAttribute(a_position);

  // get uniforms.
  var u_fragcolor = gl.getUniformLocation(gl.program, 'u_FragColor');
  checkUniform(u_fragcolor);
  var u_matrix = gl.getUniformLocation(gl.program, 'u_Matrix');
  checkUniform(u_matrix);

  // create buffer.
  var vertex_buffer = gl.createBuffer();
  if (!vertex_buffer) {
    alert("Fail to create vertex buffer!");
    return;
  }

  // bind buffer.
  gl.bindBuffer(gl.ARRAY_BUFFER, vertex_buffer);

  // dispatch attribute to buffer and enable it.
  gl.vertexAttribPointer(a_position, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(a_position);

  // write to buffer.
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(g_points), gl.STREAM_DRAW);

  var r = Math.random();
  var g = Math.random();
  var b = Math.random();
  var a = Math.random();
  gl.uniform4f(u_fragcolor, r, g, b, a);

  reset(gl, u_matrix);

  var button_translation = document.getElementById('drawTranslation');  
  button_translation.onclick = function() {
    var valueX = document.getElementById('translationX').value;
    valueX = parseFloat(valueX) * 10 / 600 - 0.5;
    var valueY = document.getElementById('translationY').value;
    valueY = parseFloat(valueY) * 10 / 600 - 0.5;

    translate(gl, u_matrix, valueX, valueY);
  };

  var button_scale = document.getElementById('drawScale');  
  button_scale.onclick = function() {
    var valueX = document.getElementById('scaleX').value;
    valueX = parseFloat(valueX) / 5;
    var valueY = document.getElementById('scaleY').value;
    valueY = parseFloat(valueY) / 5;

    scale(gl, u_matrix, valueX, valueY);
  };

  var button_rotate = document.getElementById('drawRotate');  
  button_rotate.onclick = function() {
    var value = document.getElementById('rotateAngle').value;
    rotate(gl, u_matrix, value);
  };

  var button_reset = document.getElementById('drawReset');  
  button_reset.onclick = function() {
    reset(gl, u_matrix);
  };
};
