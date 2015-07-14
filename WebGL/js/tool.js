// get webgl context on different platforms.
function getWebGLContext(canvas) {
  var webGLContext;
  /* Context name can differ according to the browser used */
  /* Store the context name in an array and check its validity */
  var names = ["webgl2", "experimental-webgl2", "webkit-3d", "moz-webgl"];
  for (var i = 0; i < names.length; ++i) {
    try {
      webGLContext = canvas.getContext(names[i]);
    } catch(e) {
      alert("Error: " + e.toString());
    }
    if (webGLContext)
      break;
  }

  return webGLContext;
}

// clear gl buffer.
function clearBuffer(gl) {
  gl.clearColor(0.0, 0.0, 0.0, 1.0);
  gl.clear(gl.COLOR_BUFFER_BIT);
}

// shader.
var Shader = function (gl, type, source) {
  var shader = gl.createShader(type);
  gl.shaderSource(shader, source);
  gl.compileShader(shader);

  if (gl.getShaderParameter(shader, gl.COMPILE_STATUS) === false) {
    alert("Could not compile shaders");
    return null;
  }

  return shader;
};

// init shaders.
function initShaders(gl, vshader_source, fshader_source) {
  var vshader = Shader(gl, gl.VERTEX_SHADER, vshader_source);
  var fshader = Shader(gl, gl.FRAGMENT_SHADER, fshader_source);

  if (vshader === null || fshader === null) {
    return false;
  }

  var shaderProgram = gl.createProgram();
  gl.attachShader(shaderProgram, vshader);
  gl.attachShader(shaderProgram, fshader);
  gl.linkProgram(shaderProgram);

  if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
    alert("Could not initialise shaders");
    return false;
  }

  gl.useProgram(shaderProgram);
  gl.program = shaderProgram;

  return true;
}

// check attribute location.
function checkAttribute(attribute) {
  if (attribute < 0) {
    alert("Failed to get attribute location of gl program.");
    return false;
  }

  return true;
}

// check uniform location.
function checkUniform(uniform) {
  if (!uniform) {
    alert("Failed to get uniform location of gl program.");
    return false;
  }

  return true;
}
