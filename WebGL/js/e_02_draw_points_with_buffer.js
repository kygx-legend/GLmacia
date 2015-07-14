// points.
var g_points = [];

// on mouse down event.
function click(ev, gl, canvas, position, size, color) {
  var x = ev.clientX;
  var y = ev.clientY;
  var rect = ev.target.getBoundingClientRect();

  x = ((x - rect.left) - canvas.width / 2) / (canvas.width / 2);
  y = (canvas.height / 2 - (y - rect.top)) / (canvas.height/ 2);
  g_points.push(x);
  g_points.push(y);

  var r = Math.random();
  var g = Math.random();
  var b = Math.random();
  var a = Math.random();

  clearBuffer(gl);

  gl.vertexAttrib1f(size, Math.random() * 20 + 2);
  gl.uniform4f(color, r, g, b, a);

  // write to buffer.
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(g_points), gl.DYNAMIC_DRAW);

  // draw with buffer.
  gl.drawArrays(gl.POINTS, 0, g_points.length / 2);
}

// main function.
function main() {
  var VSHADER_SOURCE =
      'attribute vec4 a_Position;\n' +
      'attribute float a_PointSize;\n' +
      'void main() {\n' +
      '  gl_Position = a_Position;\n' +
      '  gl_PointSize = a_PointSize;\n' +
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
  var a_pointsize = gl.getAttribLocation(gl.program, 'a_PointSize');
  checkAttribute(a_pointsize);

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

  // dispatch attribute to buffer and enable it.
  gl.vertexAttribPointer(a_position, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(a_position);

  canvas.onmousedown = function (ev) {
    click(ev, gl, canvas, a_position, a_pointsize, u_fragcolor);
  };

  clearBuffer(gl);
};
