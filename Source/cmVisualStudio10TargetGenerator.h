/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmVisualStudioTargetGenerator_h
#define cmVisualStudioTargetGenerator_h

#include "cmConfigure.h" // IWYU pragma: keep

#include <iosfwd>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

class cmComputeLinkInformation;
class cmCustomCommand;
class cmGeneratedFileStream;
class cmGeneratorTarget;
class cmGlobalVisualStudio10Generator;
class cmLocalVisualStudio7Generator;
class cmMakefile;
class cmSourceFile;
class cmSourceGroup;
class cmVS10GeneratorOptions;

class cmVisualStudio10TargetGenerator
{
  CM_DISABLE_COPY(cmVisualStudio10TargetGenerator)

public:
  cmVisualStudio10TargetGenerator(cmGeneratorTarget* target,
                                  cmGlobalVisualStudio10Generator* gg);
  ~cmVisualStudio10TargetGenerator();
  void Generate();
  // used by cmVisualStudioGeneratorOptions
  void WritePlatformConfigTag(const char* tag, const std::string& config,
                              int indentLevel, const char* attribute = 0);

private:
  struct ToolSource
  {
    cmSourceFile const* SourceFile;
    bool RelativePath;
  };
  struct ToolSources : public std::vector<ToolSource>
  {
  };

  struct TargetsFileAndConfigs
  {
    std::string File;
    std::vector<std::string> Configs;
  };

  struct Elem;

  std::string ConvertPath(std::string const& path, bool forceRelative);
  void WriteString(const char* line, int indentLevel);
  void WriteElem(const char* tag, const char* val, int indentLevel);
  void WriteElem(const char* tag, std::string const& val, int indentLevel);
  void WriteElemEscapeXML(const char* tag, std::string const& val,
                          int indentLevel);
  void WriteProjectConfigurations();
  void WriteProjectConfigurationValues();
  void WriteMSToolConfigurationValues(std::string const& config);
  void WriteMSToolConfigurationValuesManaged(std::string const& config);
  void WriteHeaderSource(cmSourceFile const* sf);
  void WriteExtraSource(cmSourceFile const* sf);
  void WriteNsightTegraConfigurationValues(std::string const& config);
  void WriteSource(std::string const& tool, cmSourceFile const* sf);
  void WriteExcludeFromBuild(Elem&,
                             std::vector<size_t> const& exclude_configs);
  void WriteAllSources();
  void WriteDotNetReferences();
  void WriteDotNetReference(std::string const& ref, std::string const& hint);
  void WriteDotNetReferenceCustomTags(std::string const& ref);
  void WriteEmbeddedResourceGroup();
  void WriteWinRTReferences();
  void WriteWinRTPackageCertificateKeyFile();
  void WriteXamlFilesGroup();
  void WritePathAndIncrementalLinkOptions();
  void WriteItemDefinitionGroups();
  void VerifyNecessaryFiles();
  void WriteMissingFiles();
  void WriteMissingFilesWP80();
  void WriteMissingFilesWP81();
  void WriteMissingFilesWS80();
  void WriteMissingFilesWS81();
  void WriteMissingFilesWS10_0();
  void WritePlatformExtensions();
  void WriteSinglePlatformExtension(std::string const& extension,
                                    std::string const& version);
  void WriteSDKReferences();
  void WriteSingleSDKReference(std::string const& extension,
                               std::string const& version);
  void WriteCommonMissingFiles(const std::string& manifestFile);
  void WriteTargetSpecificReferences();
  void WriteTargetsFileReferences();

  std::vector<std::string> GetIncludes(std::string const& config,
                                       std::string const& lang) const;

  bool ComputeClOptions();
  bool ComputeClOptions(std::string const& configName);
  void WriteClOptions(std::string const& config);
  bool ComputeRcOptions();
  bool ComputeRcOptions(std::string const& config);
  void WriteRCOptions(std::string const& config);
  bool ComputeCudaOptions();
  bool ComputeCudaOptions(std::string const& config);
  void WriteCudaOptions(std::string const& config);

  bool ComputeCudaLinkOptions();
  bool ComputeCudaLinkOptions(std::string const& config);
  void WriteCudaLinkOptions(std::string const& config);

  bool ComputeMasmOptions();
  bool ComputeMasmOptions(std::string const& config);
  void WriteMasmOptions(std::string const& config);
  bool ComputeNasmOptions();
  bool ComputeNasmOptions(std::string const& config);
  void WriteNasmOptions(std::string const& config);

  bool ComputeLinkOptions();
  bool ComputeLinkOptions(std::string const& config);
  bool ComputeLibOptions();
  bool ComputeLibOptions(std::string const& config);
  void WriteLinkOptions(std::string const& config);
  void WriteMidlOptions(std::string const& config);
  void WriteAntBuildOptions(std::string const& config);
  void OutputLinkIncremental(std::string const& configName);
  void WriteCustomRule(cmSourceFile const* source,
                       cmCustomCommand const& command);
  void WriteCustomRuleCpp(std::string const& config, std::string const& script,
                          std::string const& inputs,
                          std::string const& outputs,
                          std::string const& comment);
  void WriteCustomRuleCSharp(std::string const& config,
                             std::string const& commandName,
                             std::string const& script,
                             std::string const& inputs,
                             std::string const& outputs,
                             std::string const& comment);
  void WriteCustomCommands();
  void WriteCustomCommand(cmSourceFile const* sf);
  void WriteGroups();
  void WriteProjectReferences();
  void WriteApplicationTypeSettings();
  void OutputSourceSpecificFlags(Elem&, cmSourceFile const* source);
  void AddLibraries(cmComputeLinkInformation& cli,
                    std::vector<std::string>& libVec,
                    std::vector<std::string>& vsTargetVec);
  void AddTargetsFileAndConfigPair(std::string const& targetsFile,
                                   std::string const& config);
  void WriteLibOptions(std::string const& config);
  void WriteManifestOptions(std::string const& config);
  void WriteEvents(std::string const& configName);
  void WriteEvent(const char* name,
                  std::vector<cmCustomCommand> const& commands,
                  std::string const& configName);
  void WriteGroupSources(Elem& e0, std::string const& name,
                         ToolSources const& sources,
                         std::vector<cmSourceGroup>&);
  void AddMissingSourceGroups(std::set<cmSourceGroup*>& groupsUsed,
                              const std::vector<cmSourceGroup>& allGroups);
  bool IsResxHeader(const std::string& headerFile);
  bool IsXamlHeader(const std::string& headerFile);
  bool IsXamlSource(const std::string& headerFile);

  bool ForceOld(const std::string& source) const;

  void GetCSharpSourceProperties(cmSourceFile const* sf,
                                 std::map<std::string, std::string>& tags);
  void WriteCSharpSourceProperties(
    const std::map<std::string, std::string>& tags);
  void GetCSharpSourceLink(cmSourceFile const* sf, std::string& link);

private:
  typedef cmVS10GeneratorOptions Options;
  typedef std::map<std::string, std::unique_ptr<Options>> OptionsMap;
  OptionsMap ClOptions;
  OptionsMap RcOptions;
  OptionsMap CudaOptions;
  OptionsMap CudaLinkOptions;
  OptionsMap MasmOptions;
  OptionsMap NasmOptions;
  OptionsMap LinkOptions;
  std::string LangForClCompile;
  std::string PathToProjectFile;
  std::string ProjectFileExtension;
  enum VsProjectType
  {
    vcxproj,
    csproj
  } ProjectType;
  bool InSourceBuild;
  std::vector<std::string> Configurations;
  std::vector<TargetsFileAndConfigs> TargetsFileAndConfigsVec;
  cmGeneratorTarget* const GeneratorTarget;
  cmMakefile* const Makefile;
  std::string const Platform;
  std::string const Name;
  std::string const GUID;
  bool MSTools;
  bool Managed;
  bool NsightTegra;
  int NsightTegraVersion[4];
  bool TargetCompileAsWinRT;
  cmGlobalVisualStudio10Generator* const GlobalGenerator;
  cmGeneratedFileStream* BuildFileStream;
  cmLocalVisualStudio7Generator* const LocalGenerator;
  std::set<cmSourceFile const*> SourcesVisited;
  std::set<std::string> CSharpCustomCommandNames;
  bool IsMissingFiles;
  std::vector<std::string> AddedFiles;
  std::string DefaultArtifactDir;

  typedef std::map<std::string, ToolSources> ToolSourceMap;
  ToolSourceMap Tools;
  std::string GetCMakeFilePath(const char* name) const;
};

#endif
