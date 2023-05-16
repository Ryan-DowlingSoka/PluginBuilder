// Copyright 2022-2023 Naotsun. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PluginBuilder/PluginBuilderGlobals.h"

namespace PluginBuilder
{
	/**
	 * A dataset used to process plugin build.
	 */
	struct PLUGINBUILDER_API FBuildPluginParams
	{
	public:
		// A name of the plugin to build.
		FString PluginName;

		// A friendly name of the plugin to build.
		FString PluginFriendlyName;

		//Whether to use friendly names in plugin output files, editor menus, etc.
		bool bUseFriendlyName = true;
		
		// A version name of the plugin to build.
		FString PluginVersionName;

		// Whether the plugin to build uses the content folder.
		bool bCanPluginContainContent = false;
		
		// A path to the .uplugin file for the plugin you want to build.
		FString UPluginFile;

		// A path of the directory where pre-built plugins, zipped plugins, etc. are output.
		TOptional<FString> OutputDirectoryPath;
		
		// A list of target platforms to build the plugin.
		TArray<FString> TargetPlatforms;
		
		// Whether to handle older versions that do not use the Rocket.txt file.
		bool bRocket = false;

		// Whether to create a subfolder in the output built plugins folder.
		bool bCreateSubFolder = false;

		// Whether to judge the header inclusion of the plug-in code strictly.
		bool bStrictIncludes = false;

		// Whether to create a zip file that contains only the files we need after the build.
		bool bZipUp = false;
		
		// Whether to put the zip files into a single folder. If false will use a per engine folder for each zip file.
		bool bOutputAllZipFilesToSingleFolder = false;

		// Whether the zip folder should keep the binaries folder. Marketplace submissions expect the binaries folder to be deleted.
		bool bKeepBinariesFolder = false;

		// Whether to keep the properties of uplugin that are deleted when outputting from UAT even after outputting.
		bool bKeepUPluginProperties = false;
		
		// Whether to stop the packaging process as soon as the cancel button is pressed during packaging.
		bool bStopPackagingProcessImmediately = false;

	public:
		// Returns the name of the plugin formatted according to the value of bUseFriendlyName.
		FString GetPluginNameInSpecifiedFormat() const;

		// Returns whether the format is acceptable for submission to the marketplace.
		bool IsFormatExpectedByMarketplace() const;
	};
	
	/**
	 * A dataset used to process plugin packages.
	 */
	struct PLUGINBUILDER_API FPackagePluginParams
	{
	public:
		// A list of engine versions to build the plugin.
		TArray<FString> EngineVersions;

		// A dataset used to process plugin build.
		FBuildPluginParams BuildPluginParams;

#if UE_5_00_OR_LATER
		// Whether to change the output log filter to show only log categories for this plugin when starting the package process.
		bool bShowOnlyLogsFromThisPluginWhenPackageProcessStarts = false;
#endif

	public:
		// Creates a parameter set from the values set in the editor preferences.
		static bool MakeDefault(FPackagePluginParams& Default);
		static bool MakeFromPluginFriendlyName(const FName& PluginFriendlyName, FPackagePluginParams& Params);

		// Returns whether the parameters is valid to start package plugin task.
		// Returns true if the specified plugin exists and all engine versions are installed.
		bool IsValid() const;
	};
}
