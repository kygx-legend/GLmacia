// points and colors.
var g_points = [];
var g_colors = [];

// on mouse down event.
function click(ev, gl, canvas, position, size, color) {
  var x = ev.clientX;
  var y = ev.clientY;
  var rect = ev.target.getBoundingClientRect();

  x = ((x - rect.left) - canvas.width / 2) / (canvas.width / 2);
  y = (canvas.height / 2 - (y - rect.top)) / (canvas.height/ 2);
  g_points.push([x, y, Math.random() * 20]);

  var r = Math.random();
  var g = Math.random();
  var b = Math.random();
  var a = Math.random();
  g_colors.push([r, g, b, a]);

  clearBuffer(gl);

  for (var i = 0; i < g_points.length; i++) {
    var xys = g_points[i];
    var rgba = g_colors[i];

    // draw one point.
    gl.vertexAttrib3f(position, xys[0], xys[1], 0.0);
    gl.vertexAttrib1f(size, xys[2]);
    gl.uniform4f(color, rgba[0], rgba[1], rgba[2], rgba[3]);
    gl.drawArrays(gl.POINTS, 0, 1);
  }
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

  canvas.onmousedown = function (ev) {
    click(ev, gl, canvas, a_position, a_pointsize, u_fragcolor);
  };

  clearBuffer(gl);
};
