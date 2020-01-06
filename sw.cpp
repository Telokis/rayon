#pragma sw require header org.sw.demo.qtproject.qt.base.tools.moc

void build(Solution& s)
{
  auto& rayon = s.addProject("rayon");

  auto& engine = rayon.addTarget<StaticLibraryTarget>("engine");
  {
    engine.CPPVersion = CPPLanguageStandard::CPP17;

    // Files
    engine.Private += "Projects/Engine/Source/.*"_rr;
    engine.Private += "Projects/Engine/Include/.*"_rr;
    engine.Private += "Dependencies/json/Json.cpp";
    engine.Private += "Dependencies/json/Json.h";
    engine.Private += "Dependencies/json/Json-forwards.h";

    // Dependencies
    engine.Private += "org.sw.demo.boost.filesystem-1.72.0"_dep;

    // Include directories
    engine.Public += "Projects/Engine/Include"_id;
    engine.Public += "Dependencies/json"_id;
    engine.Public += "Dependencies/glm/include"_id;

    engine.ApiName = "RAYON_ENGINE_API";
  }

  auto& cli = rayon.addTarget<ExecutableTarget>("cli");
  {
    cli.CPPVersion = CPPLanguageStandard::CPP17;

    // Files
    cli.Private += "Projects/CLI/Source/.*"_rr;
    cli.Private += "Projects/CLI/Include/.*"_rr;
    cli.Private += "Projects/Engine/Include/.*"_rr;
    cli.Private += "Dependencies/json/Json-forwards.h";

    // Dependencies
    cli.Private += engine;
    cli.Private += "org.sw.demo.boost.filesystem-1.72.0"_dep;
    cli.Private += "org.sw.demo.boost.program_options-1.72.0"_dep;

    // Include directories
    cli.Private += "Projects/CLI/Include/"_id;
    cli.Private += "Dependencies/glm/include"_id;
  }

  auto& bench = rayon.addTarget<ExecutableTarget>("bench");
  {
    bench.CPPVersion = CPPLanguageStandard::CPP17;

    // Files
    bench.Private += "Projects/Bench/Source/.*"_rr;
    bench.Private += "Projects/Engine/Include/.*"_rr;
    bench.Private += "Dependencies/json/Json-forwards.h";

    // Dependencies
    bench.Private += engine;
    bench.Private += "pub.telokis.github.google.benchmark-1.5.0"_dep;

    // Include directories
    bench.Private += "Dependencies/glm/include"_id;
  }

  auto& gui = rayon.addTarget<ExecutableTarget>("gui");
  {
    gui.CPPVersion = CPPLanguageStandard::CPP17;

    // Files
    gui.Private += "Projects/GUI/Source/.*"_rr;
    gui.Private += "Projects/GUI/Include/.*"_rr;
    gui.Private += "Projects/GUI/Form/.*"_rr;
    gui.Private += "Projects/GUI/Resources/.*"_rr;
    gui.Private += "Projects/Engine/Include/.*"_rr;
    gui.Private += "Dependencies/json/Json.cpp";
    gui.Private += "Dependencies/json/Json.h";
    gui.Private += "Dependencies/json/Json-forwards.h";

    // Dependencies
    gui.Private += engine;
    gui.Private += "org.sw.demo.boost.filesystem-1.72.0"_dep;
    gui.Private
      += "pub.telokis.qt_with_fusion.qtproject.qt.base.plugins.platforms.windows-5.14.0"_dep;
    gui.Private += "pub.telokis.qt_with_fusion.qtproject.qt.base.widgets-5.14.0"_dep;

    // Include directories
    gui.Private += "Projects/GUI/Include/"_id;
    gui.Private += "Dependencies/json"_id;
    gui.Private += "Dependencies/glm/include"_id;

    qt_moc_rcc_uic("org.sw.demo.qtproject.qt"_dep, gui);
  }
}