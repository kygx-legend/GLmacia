var LeMatrix4 = function() {
  this.elements = new Float32Array([1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1]);
};

LeMatrix4.prototype.set = function(other) {
  if (other.elements === this.elements) {
    return;
  }

  for (var i = 0; i < 16; ++i) {
    this.elements[i] = other.elements[i];
  }

  return this;
};

LeMatrix4.prototype.multiply = function(other) {
  var e = this.elements;
  var a = this.elements;
  var b = other.elements;

  if (e === b) {
    b = new Float32Array(16);
    for (var i = 0; i < 16; ++i) {
      b[i] = e[i];
    }
  }

  for (i = 0; i < 4; i++) {
    var ai0 = a[i];
    var ai1 = a[i+4];
    var ai2 = a[i+8];
    var ai3 = a[i+12];
    e[i] = ai0 * b[0] + ai1 * b[1] + ai2 * b[2] + ai3 * b[3];
    e[i+4] = ai0 * b[4] + ai1 * b[5] + ai2 * b[6] + ai3 * b[7];
    e[i+8] = ai0 * b[8] + ai1 * b[9] + ai2 * b[10] + ai3 * b[11];
    e[i+12] = ai0 * b[12] + ai1 * b[13] + ai2 * b[14] + ai3 * b[15];
  }

  return this;
};

LeMatrix4.prototype.setScale = function(x, y, z) {
  var e = this.elements;
  e[0] = x; e[4] = 0; e[8] = 0; e[12] = 0;
  e[1] = 0; e[5] = y; e[9] = 0; e[13] = 0;
  e[2] = 0; e[6] = 0; e[10] = z; e[14] = 0;
  e[3] = 0; e[7] = 0; e[11] = 0; e[15] = 1;
  return this;
};

LeMatrix4.prototype.scale = function(x, y, z) {
  var e = this.elements;
  e[0] *= x; e[4] *= y; e[8] *= z;
  e[1] *= x; e[5] *= y; e[9] *= z;
  e[2] *= x; e[6] *= y; e[10] *= z;
  e[3] *= x; e[7] *= y; e[11] *= z;
  return this;
};

LeMatrix4.prototype.setTranslate = function(x, y, z) {
  var e = this.elements;
  e[0] = 1; e[4] = 0; e[8] = 0; e[12] = x;
  e[1] = 0; e[5] = 1; e[9] = 0; e[13] = y;
  e[2] = 0; e[6] = 0; e[10] = 1; e[14] = z;
  e[3] = 0; e[7] = 0; e[11] = 0; e[15] = 1;
  return this;
};

LeMatrix4.prototype.translate = function(x, y, z) {
  var e = this.elements;
  e[12] += e[0] * x + e[4] * y + e[8] * z;
  e[13] += e[1] * x + e[5] * y + e[9] * z;
  e[14] += e[2] * x + e[6] * y + e[10] * z;
  e[15] += e[3] * x + e[7] * y + e[11] * z;
  return this;
};

LeMatrix4.prototype.setRotate = function(angle, x, y, z) {
  var angle = Math.PI * angle / 180;
  var e = this.elements;
  var s = Math.sin(angle);
  var c = Math.cos(angle);
  if (0 !== x && 0 === y && 0 === z) {
    // X
    if (x < 0) {
      s = -s;
    }
    e[0] = 1; e[4] = 0; e[ 8] = 0; e[12] = 0;
    e[1] = 0; e[5] = c; e[ 9] =-s; e[13] = 0;
    e[2] = 0; e[6] = s; e[10] = c; e[14] = 0;
    e[3] = 0; e[7] = 0; e[11] = 0; e[15] = 1;
  } else if (0 === x && 0 !== y && 0 === z) {
    // Y
    if (y < 0) {
      s = -s;
    }
    e[0] = c; e[4] = 0; e[ 8] = s; e[12] = 0;
    e[1] = 0; e[5] = 1; e[ 9] = 0; e[13] = 0;
    e[2] =-s; e[6] = 0; e[10] = c; e[14] = 0;
    e[3] = 0; e[7] = 0; e[11] = 0; e[15] = 1;
  } else if (0 === x && 0 === y && 0 !== z) {
    // Z
    if (z < 0) {
      s = -s;
    }
    e[0] = c; e[4] =-s; e[ 8] = 0; e[12] = 0;
    e[1] = s; e[5] = c; e[ 9] = 0; e[13] = 0;
    e[2] = 0; e[6] = 0; e[10] = 1; e[14] = 0;
    e[3] = 0; e[7] = 0; e[11] = 0; e[15] = 1;
  } else {
    // any
    var len = Math.sqrt(x*x + y*y + z*z);
    if (len !== 1) {
      var rlen = 1 / len;
      x *= rlen;
      y *= rlen;
      z *= rlen;
    }
    var nc, xy, yz, zx, xs, ys, zs;
    nc = 1 - c;
    xy = x * y;
    yz = y * z;
    zx = z * x;
    xs = x * s;
    ys = y * s;
    zs = z * s;
    e[ 0] = x * x * nc + c;
    e[ 1] = xy * nc + zs;
    e[ 2] = zx * nc - ys;
    e[ 3] = 0;
    e[ 4] = xy * nc - zs;
    e[ 5] = y * y * nc + c;
    e[ 6] = yz * nc + xs;
    e[ 7] = 0;
    e[ 8] = zx * nc + ys;
    e[ 9] = yz * nc - xs;
    e[10] = z * z * nc + c;
    e[11] = 0;
    e[12] = 0;
    e[13] = 0;
    e[14] = 0;
    e[15] = 1;
  }
  return this;
};

LeMatrix4.prototype.rotate = function(angle, x, y, z) {
  return this.multiply(new LeMatrix4().setRotate(angle, x, y, z));
};
