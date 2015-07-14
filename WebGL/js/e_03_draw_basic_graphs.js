// points.
var g_points = [
    -0.8, -0.8,  // 1 - III.
    -0.6, 0.5,   // 2 - II.
    -0.4, -0.8,  // 3 - III.
    0.1, 0.7,    // 4 - I.
    0.5, -0.7,   // 5 - IV.
    0.8, 0.7,    // 6 - I.
];

// methods.
var METHODS = {
    0: 'gl.POINTS',          // points.
    1: 'gl.LINES',           // lines.
    2: 'gl.LINE_LOOP',       // loop lines.
    3: 'gl.LINE_STRIP',      // strip lines.
    4: 'gl.TRIANGLES',       // triangles.
    5: 'gl.TRIANGLE_STRIP',  // strip triangles.
    6: 'gl.TRIANGLE_FAN',    // fan triangles. 
};

// click function.
function click(gl, methods, current_method, color) {
  var r = Math.random();
  var g = Math.random();
  var b = Math.random();
  var a = Math.random();

  clearBuffer(gl);

  gl.uniform4f(color, r, g, b, a);

  gl.drawArrays(methods[current_method], 0, g_points.length / 2);

  document.getElementById('method').innerHTML = 'Methods: ' + METHODS[current_method];
}

// main function.
function main() {
  var VSHADER_SOURCE =
      'attribute vec4 a_Position;\n' +
      'void main() {\n' +
      '  gl_Position = a_Position;\n' +
      '  gl_PointSize = 10.0;\n' +
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

  // create buffer.
  var vertex_buffer = gl.createBuffer();
  if (!vertex_buffer) {
    alert("Fail to create vertex buffer!");
    return;
  }

  // bind buffer.
  gl.bindBuffer(gl.ARRAY_BUFFER, vertex_buffer);

  // write to buffer.
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(g_points), gl.STATIC_DRAW);

  // dispatch attribute to buffer and enable it.
  gl.vertexAttribPointer(a_position, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(a_position);

  // draw methods.
  var methods = [
      gl.POINTS,          // points.
      gl.LINES,           // lines.
      gl.LINE_LOOP,       // loop lines.
      gl.LINE_STRIP,      // strip lines.
      gl.TRIANGLES,       // triangles.
      gl.TRIANGLE_STRIP,  // strip triangles.
      gl.TRIANGLE_FAN,    // fan triangles. 
  ];

  // current method.
  var current_method = 0;

  canvas.onmousedown = function (ev) {
    if (current_method > 6) {
      current_method = 0;
    }

    click(gl, methods, current_method, u_fragcolor);

    current_method += 1;
  };

  clearBuffer(gl);
};
