function mulberry32(a) {
  return () => {
    a += 0x6d2b79f5;
    let t = a;
    t = Math.imul(t ^ (t >>> 15), t | 1);
    t ^= t + Math.imul(t ^ (t >>> 7), t | 61);
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  };
}

const random = new (class {
  constructor() {
    const seed = require("crypto")
      .randomBytes(2)
      .readInt16BE();
    console.log(seed);
    this.generator = mulberry32(seed);
  }

  /**
   * Picks a random item from an array.
   *
   * @param {Array} array Array to pick an item from
   */
  arrayItem(array) {
    return array[Math.floor(this.float() * array.length)];
  }

  /**
   * Generates either true or false.
   */
  boolean() {
    return this.float() > 0.5;
  }

  /**
   *
   * @param {Array<[number, any]>} data The array of weight, value pairs.
   */
  weighted(data) {
    const weights = data.map(d => d[0]);

    const sum = weights.reduce((s, w) => s + w, 0);

    if (isNaN(sum)) {
      throw new Error("There is an invalid weight. Weights sum was NaN");
    }

    const selected = this.float() * sum;
    let acc = 0;

    for (let i = 0; i < weights.length; ++i) {
      const weight = weights[i];

      acc += weight;
      if (selected <= acc) {
        return data[i][1];
      }
    }

    return data[weights.length - 1][1];
  }

  /**
   * Generates a random integer number between the given bounds.
   * If min is specified but max is omitted, max = min and min = 0.
   * If neither is specified, min = 0 and max = MAX_INT.
   * min and max can be returned.
   *
   * @param {integer} min Inclusive
   * @param {integer} max Inclusive
   */
  int(min, max) {
    if (max === undefined) {
      max = min;
      min = 0;
    }

    if (min === undefined) {
      min = 0;
      max = 214746483647;
    }

    min = Math.ceil(min);
    max = Math.floor(max);

    return Math.floor(this.float() * (max - min + 1)) + min;
  }

  /**
   * Generates a number between 0 and 1.
   */
  float() {
    return this.generator();
  }

  /**
   * Generates a number between 0 and 1.
   */
  floating({ fixed, min, max }) {
    const p = Math.pow(10, fixed);

    return Math.floor((this.float() * (max - min + 1) + min) * p) / p;
  }
})();

const textures = [
  "./files/scenes/textures/2k_ceres_fictional.jpg",
  "./files/scenes/textures/2k_makemake_fictional.jpg",
  "./files/scenes/textures/2k_stars.jpg",
  "./files/scenes/textures/2k_earth_daymap.jpg",
  "./files/scenes/textures/2k_mars.jpg",
  "./files/scenes/textures/2k_stars_milky_way.jpg",
  "./files/scenes/textures/2k_earth_nightmap.jpg",
  "./files/scenes/textures/2k_mercury.jpg",
  "./files/scenes/textures/2k_sun.jpg",
  "./files/scenes/textures/2k_eris_fictional.jpg",
  "./files/scenes/textures/2k_moon.jpg",
  "./files/scenes/textures/2k_uranus.jpg",
  "./files/scenes/textures/2k_haumea_fictional.jpg",
  "./files/scenes/textures/2k_neptune.jpg",
  "./files/scenes/textures/2k_venus_atmosphere.jpg",
  "./files/scenes/textures/2k_jupiter.jpg",
  "./files/scenes/textures/2k_saturn.jpg",
  "./files/scenes/textures/2k_venus_surface.jpg"
];

const colors = [
  "black",
  "white",
  "red",
  "green",
  "blue",
  "deeppink4",
  "silver",
  "gray",
  "maroon",
  "yellow",
  "olive",
  "lime",
  "aqua",
  "teal",
  "navy",
  "fuchsia",
  "purple"
];

const flags = [
  "NoShadow",
  "NoImage",
  "NoReflection",
  "NoTransparency",
  "NoShading"
];

const randomTextureMaterial = () => {
  return {
    type: "Texture",
    filepath: random.arrayItem(textures)
  };
};

const randomCheckerboardMaterial = () => {
  const res = {
    type: "Checkerboard",
    scale: random.floating({ fixed: 2, min: 0.1, max: 10 }),
    tiles: [randomMaterial(), randomMaterial()]
  };

  if (
    random.weighted([
      [1, "y"],
      [4, "n"]
    ]) === "y"
  ) {
    res.tiles.push(randomMaterial());
  }

  if (
    random.weighted([
      [1, "y"],
      [8, "n"]
    ]) === "y"
  ) {
    res.tiles.push(randomMaterial());
  }

  return res;
};

const randomPlainMaterial = () => {
  const res = {
    type: "Plain",
    ambient: -1,
    glossiness: 0,
    reflexion: 0,
    refraction: 1,
    shininess: 0,
    transparency: 0,
    flags: []
  };

  // if (random.boolean()) {
  //   res.color = random.arrayItem(colors);
  // } else {
  res.color = {
    red: random.int(0, 255),
    green: random.int(0, 255),
    blue: random.int(0, 255)
  };
  // }

  flags.forEach(flag => {
    if (
      random.weighted([
        [1, "y"],
        [9, "n"]
      ]) === "y"
    ) {
      res.flags.push(flag);
    }
  });

  // if (random.weighted([[1, "y"],[3, "n"]]) === "y") {
  //     res.ambient = random.weighted([[5, 0.1], [2, 0.3],[1, 1]]);
  // }

  if (
    random.weighted([
      [1, "y"],
      [3, "n"]
    ]) === "y"
  ) {
    res.glossiness = random.floating({ fixed: 1, min: 0.1, max: 1.0 });
  }

  if (
    random.weighted([
      [1, "y"],
      [2, "n"]
    ]) === "y"
  ) {
    res.reflexion = random.floating({ fixed: 1, min: 0.1, max: 1.0 });
  }

  // if (random.weighted([[1, "y"],[3, "n"]]) === "y") {
  //     res.refraction = random.floating({ fixed: 1, min: 0.5, max: 1.5 });
  // }

  if (
    random.weighted([
      [1, "y"],
      [2, "n"]
    ]) === "y"
  ) {
    res.shininess = random.floating({ fixed: 1, min: 5, max: 8 });
  }

  if (
    random.weighted([
      [1, "y"],
      [3, "n"]
    ]) === "y"
  ) {
    res.transparency = random.floating({ fixed: 1, min: 0.1, max: 0.9 });
  }

  return res;
};

const randomMaterial = () => {
  return random.weighted([
    [5, randomPlainMaterial],
    [2, randomCheckerboardMaterial],
    [3, randomTextureMaterial]
  ])();
};

const makeSphere = (x, z, r) => {
  const res = {
    position: {
      y: r,
      z,
      x
    },
    radius: r,
    type: "Sphere"
  };

  res.material = randomMaterial();

  return res;
};

const data = {
  eye: {
    position: {
      y: 100
    },
    rotation: {
      x: 90
    }
  },
  lights: [
    {
      position: {
        x: 0,
        y: 20,
        z: 0
      },
      type: "Sun"
    },
    {
      position: {
        x: 0,
        y: 5,
        z: 0
      },
      type: "Sun"
    }
  ],
  objects: [
    {
      material: {
        type: "Plain",
        color: "swimming pool",
        reflexion: 0.5
      },
      position: {
        y: 0
      },
      type: "Plane"
    }
  ]
};

let radius = 0;
for (
  x = -99;
  x < 99;
  x += radius + random.floating({ min: 2.2, max: 5, fixed: 1 })
) {
  for (
    y = -99;
    y < 99;
    y += radius + random.floating({ min: 2.2, max: 5, fixed: 1 })
  ) {
    radius = random.floating({ min: 1.5, max: 2.5, fixed: 1 });
    data.objects.push(
      makeSphere(
        x + random.floating({ min: -1.5, max: 1.5, fixed: 1 }),
        y + random.floating({ min: -1.5, max: 1.5, fixed: 1 }),
        radius
      )
    );
  }
}

console.log("Objects count :", data.objects.length);

const fs = require("fs");
const path = require("path");

fs.writeFileSync(
  path.resolve(__dirname, "../files/scenes/", "big.yon"),
  JSON.stringify(data, null, 4)
);
