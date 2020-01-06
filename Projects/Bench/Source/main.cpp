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

static void BM_RayonRunBasic_NoPreprocessing(benchmark::State& state)
{
  Rayon::Config   config(1024, 1024, 4);
  Rayon::RawImage img;
  Rayon::Scene    scene;
  Rayon::Rayon    engine(config.setSilent(true));

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);
  scene.preprocess();

  for (auto _ : state)
    engine.run(img, scene, false);
}
BENCHMARK(BM_RayonRunBasic_NoPreprocessing)->UseRealTime()->Unit(benchmark::kMillisecond);

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
BENCHMARK(BM_RayonRunBasic_WithPreprocessing)->UseRealTime()->Unit(benchmark::kMillisecond);

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
BENCHMARK(BM_RayonRunBasic_OneThread)->UseRealTime()->Unit(benchmark::kMillisecond);

static void BM_RayonRunBasic_OneThreadForced(benchmark::State& state)
{
  Rayon::Config   config(1024, 1024, 1);
  Rayon::RawImage img;
  Rayon::Scene    scene;
  Rayon::Rayon    engine(config.setSilent(true).setForceUseThread(true));

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);
  scene.preprocess();

  for (auto _ : state)
    engine.run(img, scene, false);
}
BENCHMARK(BM_RayonRunBasic_OneThreadForced)->UseRealTime()->Unit(benchmark::kMillisecond);

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
BENCHMARK(BM_RayonRunBasic_EightThread)->UseRealTime()->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();