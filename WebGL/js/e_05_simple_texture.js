// init vertex.
function initVertex(gl) {
  // get attributes.
  var a_position = gl.getAttribLocation(gl.program, 'a_Position');
  checkAttribute(a_position);
  var a_texcoord = gl.getAttribLocation(gl.program, 'a_TexCoord');
  checkAttribute(a_texcoord);

  // vertex and tex coord.
  var vertex_and_tex_coord = new Float32Array([
      -0.5, 0.5, 0.0, 1.0,
      -0.5, -0.5, 0.0, 0.0,
      0.5, 0.5, 1.0, 1.0,
      0.5, -0.5, 1.0, 0.0,
  ]);

  var buffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ARRAY_BUFFER, vertex_and_tex_coord, gl.STATIC_DRAW);

  var FSIZE = vertex_and_tex_coord.BYTES_PER_ELEMENT;
  gl.vertexAttribPointer(a_position, 2, gl.FLOAT, false, FSIZE * 4, 0);
  gl.enableVertexAttribArray(a_position);
  gl.vertexAttribPointer(a_texcoord, 2, gl.FLOAT, false, FSIZE * 4, FSIZE * 2);
  gl.enableVertexAttribArray(a_texcoord);

  return 4;
}

// init texture.
function initTexture(gl, n, canvas_id) {
  if (canvas_id === 'webgl') {
    var texture0 = gl.createTexture();
    var texture1 = gl.createTexture();
    var u_sampler0 = gl.getUniformLocation(gl.program, 'u_Sampler0');
    var u_sampler1 = gl.getUniformLocation(gl.program, 'u_Sampler1');
    checkUniform(u_sampler0);
    checkUniform(u_sampler1);

    var image0 = new Image();
    var image1 = new Image();

    image0.onload = function () {
      loadTextureWith2(gl, n, texture0, u_sampler0, image0, 0);
    };

    image1.onload = function () {
      loadTextureWith2(gl, n, texture1, u_sampler1, image1, 1);
    };

    image0.src = '../../resources/img/e_05_simple_texture_r_01.jpg';
    image1.src = '../../resources/img/e_05_simple_texture_r_02.jpg';
    return;
  }

  var texture = gl.createTexture();
  var u_sampler = gl.getUniformLocation(gl.program, 'u_Sampler');
  checkUniform(u_sampler);

  var image = new Image();
  image.onload = function () {
    loadTexture(gl, n, texture, u_sampler, image);
  };

  if (canvas_id === 'webgl0') {
    image.src = '../../resources/img/e_05_simple_texture_r_01.jpg';
  } else {
    image.src = '../../resources/img/e_05_simple_texture_r_02.jpg';
  }
}

// load texture.
var loaded0 = false, loaded1 = false;
function loadTextureWith2(gl, n, texture, sampler, image, unit) {
  gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);

  if (unit == 0) {
    gl.activeTexture(gl.TEXTURE0);
    loaded0 = true;
  } else {
    gl.activeTexture(gl.TEXTURE1);
    loaded1 = true;
  }

  gl.bindTexture(gl.TEXTURE_2D, texture);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
  gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, image);
  gl.uniform1i(sampler, unit);

  if (loaded0 && loaded1) {
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, n);
  }
}

function loadTexture(gl, n, texture, sampler, image, unit) {
  gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
  gl.activeTexture(gl.TEXTURE0);
  gl.bindTexture(gl.TEXTURE_2D, texture);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
  gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGB, gl.RGB, gl.UNSIGNED_BYTE, image);
  gl.uniform1i(sampler, 0);
  gl.drawArrays(gl.TRIANGLE_STRIP, 0, n);
}

// rendering.
function render(canvas_id) {
  var canvas = document.getElementById(canvas_id);
  var gl = getWebGLContext(canvas);
  var VSHADER_SOURCE = '';
  var FSHADER_SOURCE = '';

  if (canvas_id === 'webgl') {
    VSHADER_SOURCE =
        'attribute vec4 a_Position;\n' +
        'attribute vec2 a_TexCoord;\n' +
        'varying vec2 v_TexCoord;\n' +
        'void main() {\n' +
        '  gl_Position = a_Position;\n' +
        '  v_TexCoord = a_TexCoord;\n' +
        '}\n';
    FSHADER_SOURCE =
        'precision mediump float;\n' +
        'uniform sampler2D u_Sampler0;\n' +
        'uniform sampler2D u_Sampler1;\n' +
        'varying vec2 v_TexCoord;\n' +
        'void main() {\n' +
        '  vec4 color0 = texture2D(u_Sampler0, v_TexCoord);\n' +
        '  vec4 color1 = texture2D(u_Sampler1, v_TexCoord);\n' +
        '  gl_FragColor = color0 * color1;\n' +
        '}\n';
  } else {
    VSHADER_SOURCE =
        'attribute vec4 a_Position;\n' +
        'attribute vec2 a_TexCoord;\n' +
        'varying vec2 v_TexCoord;\n' +
        'void main() {\n' +
        '  gl_Position = a_Position;\n' +
        '  v_TexCoord = a_TexCoord;\n' +
        '}\n';
    FSHADER_SOURCE =
        'precision mediump float;\n' +
        'uniform sampler2D u_Sampler;\n' +
        'varying vec2 v_TexCoord;\n' +
        'void main() {\n' +
        '  gl_FragColor = texture2D(u_Sampler, v_TexCoord);\n' +
        '}\n';
  }


  if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
    alert("Fail to initialize shaders!");
    return;
  }

  return gl;
}

// main function.
function main() {
  var gl0 = render('webgl0');
  var gl1 = render('webgl1');
  var gl = render('webgl');

  var n0 = initVertex(gl0);
  var n1 = initVertex(gl1);
  var n = initVertex(gl);

  initTexture(gl0, n0, 'webgl0');
  initTexture(gl1, n1, 'webgl1');
  initTexture(gl, n, 'webgl');
};
