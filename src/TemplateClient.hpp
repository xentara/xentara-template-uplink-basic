// Copyright (c) embedded ocean GmbH
#pragma once

#include "Attributes.hpp"
#include "CustomError.hpp"

#include <xentara/memory/Array.hpp>
#include <xentara/memory/memoryResources.hpp>
#include <xentara/plugin/EnableSharedFromThis.hpp>
#include <xentara/process/Event.hpp>
#include <xentara/process/Microservice.hpp>
#include <xentara/process/MicroserviceClass.hpp>
#include <xentara/process/Task.hpp>
#include <xentara/utils/core/Uuid.hpp>
#include <xentara/utils/tools/Unique.hpp>

#include <string_view>
#include <functional>
#include <forward_list>

namespace xentara::plugins::templateUplink
{

using namespace std::literals;

/// @brief A class representing a client for specific type of service that data can be sent to.
/// @todo rename this class to something more descriptive
class TemplateClient final : public process::Microservice, public plugin::EnableSharedFromThis<TemplateClient>
{
private:
	/// @brief A structure used to store the class specific attributes within an element's configuration
	struct Config final
	{
		/// @todo Add custom config attributes
	};
	
public:
	/// @brief The class object containing meta-information about this element type
	class Class final : public process::MicroserviceClass
	{
	public:
		/// @brief Gets the global object
		static auto instance() -> Class&
		{
			return _instance;
		}

	    /// @brief Returns the array handle for the class specific attributes within an element's configuration
	    auto configHandle() const -> const auto &
        {
            return _configHandle;
        }

		/// @name Virtual Overrides for process::MicroserviceClass
		/// @{

		auto name() const -> std::u16string_view final
		{
			/// @todo change class name
			return u"TemplateClient"sv;
		}
	
		auto uuid() const -> utils::core::Uuid final
		{
			/// @todo assign a unique UUID
			return "bbbbbbbb-bbbb-bbbb-bbbb-bbbbbbbbbbbb"_uuid;
		}

		/// @}

	private:
	    /// @brief The array handle for the class specific attributes within an element's configuration
		memory::Array::ObjectHandle<Config> _configHandle { config().appendObject<Config>() };

		/// @brief The global object that represents the class
		static Class _instance;
	};

	/// @brief A handle used to access the client
	/// @todo implement a proper handle
	class Handle final : private utils::tools::Unique
	{
	};

	/// @brief Returns a handle to the client
	auto handle() const -> const Handle &
	{
		return _handle;
	}

	/// @name Virtual Overrides for process::Microservice
	/// @{

	auto createSubservice(const process::MicroserviceClass &microserviceClass, plugin::SharedFactory<process::Microservice> &factory) -> std::shared_ptr<process::Microservice> final;

	auto resolveAttribute(std::u16string_view name) -> const model::Attribute * final;

	auto readHandle(const model::Attribute &attribute) const noexcept -> data::ReadHandle final;

	auto prepare() -> void final;

	auto cleanup() -> void final;
	
	/// @}

protected:
	/// @name Virtual Overrides for process::Microservice
	/// @{

	auto loadConfig(const ConfigIntializer &initializer,
		utils::json::decoder::Object &jsonObject,
		config::Resolver &resolver,
		const FallbackConfigHandler &fallbackHandler) -> void final;

	/// @}

private:
	/// @brief A handle to the client
	Handle _handle;
};

} // namespace xentara::plugins::templateUplink