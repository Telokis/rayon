#include <benchmark/benchmark.h>

#include "Rayon.hh"
#include "Registry.hh"
#include "SceneParse.hh"

auto rawScene = R"json(
{
	"eye" :
	{
		"position" :
		{
			"z" : -5
		}
	},
	"lights" :
	[
		{
			"position" :
			{
				"x" : 2,
				"y" : 2.8,
				"z" : -3
			},
			"color":"white",
			"type" : "Sun"
		}
	],
	"objects" :
	[

		{
			"material" :
			{
				"color" : "aqua"
			},
			"radius":1,
			"type" : "Sphere"
		}
	]
}
)json";

static const auto repetitions = 100;

static void BM_RayonRunBasic_NoPreprocessing(benchmark::State& state)
{
  Rayon::Config   config(1024, 1024, 4);
  Rayon::RawImage img;
  Rayon::Scene    scene;
  Rayon::Rayon    engine(config);

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);
  scene.preprocess();

  for (auto _ : state)
    engine.run(img, scene, false);
}
BENCHMARK(BM_RayonRunBasic_NoPreprocessing)->Repetitions(repetitions);

static void BM_RayonRunBasic_WithPreprocessing(benchmark::State& state)
{
  Rayon::Config   config(1024, 1024, 4);
  Rayon::RawImage img;
  Rayon::Scene    scene;
  Rayon::Rayon    engine(config.setSilent(true));

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);

  for (auto _ : state)
    engine.run(img, scene, true);
}
BENCHMARK(BM_RayonRunBasic_WithPreprocessing)->Repetitions(repetitions);

static void BM_RayonRunBasic_OneThread(benchmark::State& state)
{
  Rayon::Config   config(1024, 1024, 1);
  Rayon::RawImage img;
  Rayon::Scene    scene;
  Rayon::Rayon    engine(config.setSilent(true));

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);
  scene.preprocess();

  for (auto _ : state)
    engine.run(img, scene, false);
}
BENCHMARK(BM_RayonRunBasic_OneThread)->Repetitions(repetitions);

static void BM_RayonRunBasic_EightThread(benchmark::State& state)
{
  Rayon::Config   config(1024, 1024, 8);
  Rayon::RawImage img;
  Rayon::Scene    scene;
  Rayon::Rayon    engine(config.setSilent(true));

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);
  scene.preprocess();

  for (auto _ : state)
    engine.run(img, scene, false);
}
BENCHMARK(BM_RayonRunBasic_EightThread)->Repetitions(repetitions);

BENCHMARK_MAIN();