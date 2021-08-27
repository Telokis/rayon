#include <benchmark/benchmark.h>

#include "Rayon.hh"
#include "Registry.hh"
#include "SceneParse.hh"
#include "Batch/LocalBatchGenerator.hh"

auto rawScene = R"rawScene(
eye:
  position:
    z: -5
lights:
  - position:
      x: 2
      y: 2.8
      z: -3
    color: white
    type: Sun
objects:
  - depth: 1
    height: 1
    material:
      type: Plain
      color:
        blue: 139
        green: 139
      refraction: 1
    position:
      y: 2.7
      z: 2.5
    rotation:
      y: 45
    type: Box
    width: 1
  - depth: 1
    height: 1
    material:
      type: Plain
      color:
        blue: 139
        green: 139
      refraction: 1
    position:
      x: -1.5
      y: 2.7
      z: 2.5
    rotation:
      y: 225
    type: Box
    width: 1
  - depth: 1
    height: 1
    material:
      type: Plain
      color:
        blue: 139
        green: 139
      refraction: 1
    position:
      x: 1.5
      y: 2.7
      z: 2.5
    rotation:
      y: -45
    type: Box
    width: 1
  - material:
      type: Plain
      ambient: -1
      color: deeppink4
      reflexion: 1
      refraction: 1
    position:
      x: 2.5
    radius: 1
    type: Sphere
  - material:
      type: Plain
      ambient: 1
      color: deeppink4
      flags:
        - NoShading
      glossiness: 2.5
      reflexion: 1
      refraction: 1
    position:
      x: -2.5
    radius: 1
    type: Sphere
  - material:
      type: Plain
      ambient: -1
      color: deeppink4
      flags:
        - NoShadow
      refraction: 1
    position:
      z: 5
    radius: 1
    type: Sphere
  - material:
      type: Plain
      ambient: -1
      color: swimming pool
      reflexion: 0.8
      refraction: 1
    position:
      y: -0.8
    type: Plane

)rawScene";

static void BM_RayonRunBasic_NoPreprocessing(benchmark::State& state)
{
  Rayon::Config              config(1024, 1024, 4);
  Rayon::RawImage            img;
  Rayon::Scene               scene;
  Rayon::Rayon               engine(config.setSilent(true));
  Rayon::LocalBatchGenerator batchGenerator{&img, 1, 1, config.getThreadCount()};

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);
  scene.preprocess();

  for (auto _ : state)
  {
    batchGenerator.reset();
    engine.run(img, scene, &batchGenerator, false);
  }
}
BENCHMARK(BM_RayonRunBasic_NoPreprocessing)
  ->UseRealTime()
  ->MinTime(5.0)
  ->Unit(benchmark::kMillisecond);

static void BM_RayonRunBasic_WithPreprocessing(benchmark::State& state)
{
  Rayon::Config              config(1024, 1024, 4);
  Rayon::RawImage            img;
  Rayon::Scene               scene;
  Rayon::Rayon               engine(config.setSilent(true));
  Rayon::LocalBatchGenerator batchGenerator{&img, 1, 1, config.getThreadCount()};

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);

  for (auto _ : state)
  {
    batchGenerator.reset();
    engine.run(img, scene, &batchGenerator, true);
  }
}
BENCHMARK(BM_RayonRunBasic_WithPreprocessing)
  ->UseRealTime()
  ->MinTime(5.0)
  ->Unit(benchmark::kMillisecond);

static void BM_RayonRunBasic_OneThread(benchmark::State& state)
{
  Rayon::Config              config(1024, 1024, 1);
  Rayon::RawImage            img;
  Rayon::Scene               scene;
  Rayon::Rayon               engine(config.setSilent(true));
  Rayon::LocalBatchGenerator batchGenerator{&img, 1, 1, config.getThreadCount()};

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);
  scene.preprocess();

  for (auto _ : state)
  {
    batchGenerator.reset();
    engine.run(img, scene, &batchGenerator, false);
  }
}
BENCHMARK(BM_RayonRunBasic_OneThread)->UseRealTime()->MinTime(5.0)->Unit(benchmark::kMillisecond);

static void BM_RayonRunBasic_OneThreadForced(benchmark::State& state)
{
  Rayon::Config              config(1024, 1024, 1);
  Rayon::RawImage            img;
  Rayon::Scene               scene;
  Rayon::Rayon               engine(config.setSilent(true).setForceUseThread(true));
  Rayon::LocalBatchGenerator batchGenerator{&img, 1, 1, config.getThreadCount()};

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);
  scene.preprocess();

  for (auto _ : state)
  {
    batchGenerator.reset();
    engine.run(img, scene, &batchGenerator, false);
  }
}
BENCHMARK(BM_RayonRunBasic_OneThreadForced)
  ->UseRealTime()
  ->MinTime(5.0)
  ->Unit(benchmark::kMillisecond);

static void BM_RayonRunBasic_EightThread(benchmark::State& state)
{
  Rayon::Config              config(1024, 1024, 8);
  Rayon::RawImage            img;
  Rayon::Scene               scene;
  Rayon::Rayon               engine(config.setSilent(true));
  Rayon::LocalBatchGenerator batchGenerator{&img, 1, 1, config.getThreadCount()};

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);
  scene.preprocess();

  for (auto _ : state)
  {
    batchGenerator.reset();
    engine.run(img, scene, &batchGenerator, false);
  }
}
BENCHMARK(BM_RayonRunBasic_EightThread)->UseRealTime()->MinTime(5.0)->Unit(benchmark::kMillisecond);

static void BM_RayonRunBasic_ProgressiveRPP_8T(benchmark::State& state)
{
  Rayon::Config              config(512, 512, 8);
  Rayon::RawImage            img;
  Rayon::Scene               scene;
  Rayon::Rayon               engine(config.setSilent(true));
  Rayon::LocalBatchGenerator batchGenerator{&img, -10, 1, config.getThreadCount()};

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);
  scene.preprocess();

  for (auto _ : state)
  {
    batchGenerator.reset();
    engine.run(img, scene, &batchGenerator, false);
  }
}
BENCHMARK(BM_RayonRunBasic_ProgressiveRPP_8T)
  ->UseRealTime()
  ->Iterations(50)
  ->Unit(benchmark::kMillisecond);

class BenchedBatchGenerator : public Rayon::LocalBatchGenerator
{
public:
  BenchedBatchGenerator(Rayon::RawImage* img, int rppStart, int rppEnd, Rayon::uint32 threadsCount)
    : LocalBatchGenerator(img, rppStart, rppEnd, threadsCount)
  {
  }

  bool hasNextBatch()
  {
    std::lock_guard lock(_mutex);

    return _rpp <= _rppEnd;
  }
};

static void BM_RayonRunBasic_ProgressiveRPP_NoConditionalVariable_8T(benchmark::State& state)
{
  Rayon::Config         config(512, 512, 8);
  Rayon::RawImage       img;
  Rayon::Scene          scene;
  Rayon::Rayon          engine(config.setSilent(true));
  BenchedBatchGenerator batchGenerator{&img, -10, 1, config.getThreadCount()};

  Rayon::registry().registerDefaults();
  Rayon::readSceneFromString(scene, rawScene);
  scene.preprocess();

  for (auto _ : state)
  {
    batchGenerator.reset();
    engine.run(img, scene, &batchGenerator, false);
  }
}
BENCHMARK(BM_RayonRunBasic_ProgressiveRPP_NoConditionalVariable_8T)
  ->UseRealTime()
  ->Iterations(50)
  ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();