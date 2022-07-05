#include "Config.h"
#include "GtsManager.h"
#include "hooks.h"
#include "papyrus.h"

#include <stddef.h>
#include <thread>

using namespace RE::BSScript;
using namespace Gts;
using namespace SKSE;
using namespace SKSE::log;
using namespace SKSE::stl;

namespace {


	/**
	 * Setup logging.
	 *
	 * <p>
	 * Logging is important to track issues. CommonLibSSE bundles functionality for spdlog, a common C++ logging
	 * framework. Here we initialize it, using values from the configuration file. This includes support for a debug
	 * logger that shows output in your IDE when it has a debugger attached to Skyrim, as well as a file logger which
	 * writes data to the standard SKSE logging directory at <code>Documents/My Games/Skyrim Special Edition/SKSE</code>
	 * (or <code>Skyrim VR</code> if you are using VR).
	 * </p>
	 */
	void InitializeLogging()
	{
		auto path = log_directory();

		if (!path)
		{
			report_and_fail("Unable to lookup SKSE logs directory.");
		}
		*path /= PluginDeclaration::GetSingleton()->GetName();
		*path += L".log";

		std::shared_ptr <spdlog::logger> log;

		if (IsDebuggerPresent())
		{
			log = std::make_shared <spdlog::logger>(
				"Global", std::make_shared <spdlog::sinks::msvc_sink_mt>());
		}
		else
		{
			log = std::make_shared <spdlog::logger>(
				"Global", std::make_shared <spdlog::sinks::basic_file_sink_mt>(path->string(), true));
		}

		log->set_level(spdlog::level::level_enum::info);
		log->flush_on(spdlog::level::level_enum::trace);
		log->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [%t] [%s:%#] %v");
		log->info("Logging started");
		const auto& debugConfig = Gts::Config::GetSingleton().GetDebug();

		log->set_level(debugConfig.GetLogLevel());
		log->flush_on(debugConfig.GetFlushLevel());

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [%t] [%s:%#] %v");
	}


	/**
	 * Register to listen for messages.
	 *
	 * <p>
	 * SKSE has a messaging system to allow for loosely coupled messaging. This means you don't need to know about or
	 * link with a message sender to receive their messages. SKSE itself will send messages for common Skyrim lifecycle
	 * events, such as when SKSE plugins are done loading, or when all ESP plugins are loaded.
	 * </p>
	 *
	 * <p>
	 * Here we register a listener for SKSE itself (because we have not specified a message source). Plugins can send
	 * their own messages that other plugins can listen for as well, although that is not demonstrated in this example
	 * and is not common.
	 * </p>
	 *
	 * <p>
	 * The data included in the message is provided as only a void pointer. It's type depends entirely on the type of
	 * message, and some messages have no data (<code>dataLen</code> will be zero).
	 * </p>
	 */
	void InitializeMessaging()
	{
		if (!GetMessagingInterface()->RegisterListener([](MessagingInterface::Message *message) {
			switch (message->type)
			{
				// Skyrim lifecycle events.
				case MessagingInterface::kPostLoad: // Called after all plugins have finished running SKSEPlugin_Load.
				// It is now safe to do multithreaded operations, or operations against other plugins.
				case MessagingInterface::kPostPostLoad: // Called after all kPostLoad message handlers have run.
				case MessagingInterface::kInputLoaded: // Called when all game data has been found.
					break;
				case MessagingInterface::kDataLoaded: // All ESM/ESL/ESP plugins have loaded, main menu is now active.
					// It is now safe to access form data.
					Hooks::Install();
					break;
				// Skyrim game events.
				case MessagingInterface::kPostLoadGame: // Player's selected save game has finished loading.
				// Data will be a boolean indicating whether the load was successful.

				case MessagingInterface::kNewGame: // Player starts a new game from main menu.
				case MessagingInterface::kPreLoadGame: // Player selected a game to load, but it hasn't loaded yet.
				// Data will be the name of the loaded save.
				case MessagingInterface::kSaveGame: // The player has saved a game.
				// Data will be the save name.
				case MessagingInterface::kDeleteGame: // The player deleted a saved game from within the load menu.
					break;
			}
		}))
		{
			stl::report_and_fail("Unable to register message listener.");
		}
	}
}

void InitializePapyrus() {
	log::trace("Initializing Papyrus binding...");
	if (GetPapyrusInterface()->Register(Gts::register_papyrus)) {
		log::debug("Papyrus functions bound.");
	} else {
		stl::report_and_fail("Failure to register Papyrus bindings.");
	}
}

/**
 * This if the main callback for initializing your SKSE plugin, called just before Skyrim runs its main function.
 *
 * <p>
 * This is your main entry point to your plugin, where you should initialize everything you need. Many things can't be
 * done yet here, since Skyrim has not initialized and the Windows loader lock is not released (so don't do any
 * multithreading). But you can register to listen for messages for later stages of Skyrim startup to perform such
 * tasks.
 * </p>
 */
SKSEPluginLoad(const LoadInterface * skse)
{
	InitializeLogging();

	auto *plugin  = PluginDeclaration::GetSingleton();
	auto version = plugin->GetVersion();

	log::info("{} {} is loading...", plugin->GetName(), version);


	Init(skse);
	InitializeMessaging();
	InitializePapyrus();

	log::info("{} has finished loading.", plugin->GetName());
	return(true);
}
