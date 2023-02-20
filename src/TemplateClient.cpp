// Copyright (c) embedded ocean GmbH
#include "TemplateClient.hpp"

#include "Attributes.hpp"
#include "TemplateTransaction.hpp"

#include <xentara/data/ReadHandle.hpp>
#include <xentara/memory/WriteSentinel.hpp>
#include <xentara/model/Attribute.hpp>
#include <xentara/plugin/SharedFactory.hpp>
#include <xentara/process/ExecutionContext.hpp>
#include <xentara/utils/eh/currentErrorCode.hpp>
#include <xentara/utils/json/decoder/Errors.hpp>
#include <xentara/utils/json/decoder/Object.hpp>

#include <string_view>

#ifdef _WIN32
#	include <Windows.h>
#else
#	include <errno.h>
#endif

namespace xentara::plugins::templateUplink
{

using namespace std::literals;

TemplateClient::Class TemplateClient::Class::_instance;

auto TemplateClient::loadConfig(const ConfigIntializer &initializer,
		utils::json::decoder::Object &jsonObject,
		config::Resolver &resolver,
		const FallbackConfigHandler &fallbackHandler) -> void
{
	// Get a reference that allows us to modify our own config attributes
    auto &&configAttributes = initializer[Class::instance().configHandle()];

	// Go through all the members of the JSON object that represents this object
	for (auto && [name, value] : jsonObject)
    {
		/// @todo load configuration parameters
		if (name == "TODO"sv)
		{
			/// @todo parse the value correctly
			auto todo = value.asNumber<std::uint64_t>();

			/// @todo check that the value is valid
			if (!"TODO")
			{
				/// @todo use an error message that tells the user exactly what is wrong
				utils::json::decoder::throwWithLocation(value, std::runtime_error("TODO is wrong with TODO parameter of template client"));
			}

			/// @todo set the appropriate member variables, and update configAttributes accordingly (if necessary) 
		}
		else
		{
			// Pass any unknown parameters on to the fallback handler, which will load the built-in parameters ("id", "uuid", and "children"),
			// and throw an exception if the key is unknown
            fallbackHandler(name, value);
		}
    }

	/// @todo perform consistency and completeness checks
	if (!"TODO")
	{
		/// @todo use an error message that tells the user exactly what is wrong
		utils::json::decoder::throwWithLocation(jsonObject, std::runtime_error("TODO is wrong with template client"));
	}
}

auto TemplateClient::createSubservice(const process::MicroserviceClass &ioClass, plugin::SharedFactory<process::Microservice> &factory)
	-> std::shared_ptr<process::Microservice>
{
	if (&ioClass == &TemplateTransaction::Class::instance())
	{
		return factory.makeShared<TemplateTransaction>(*this);
	}

	/// @todo add any other supported subservice types

	return nullptr;
}

auto TemplateClient::resolveAttribute(std::string_view name) -> const model::Attribute *
{
	/// @todo resolve any attributes this class supports using model::Attribute::resolve

	return nullptr;
}

auto TemplateClient::readHandle(const model::Attribute &attribute) const noexcept -> data::ReadHandle
{
	/// @todo create read handles for any readable attributes this class supports

	// Nothing found
	return data::ReadHandle::Error::Unknown;
}

auto TemplateClient::prepare() -> void
{
	/// @todo open the handle for the service instance
}

auto TemplateClient::cleanup() -> void
{
	/// @todo close the handle to the service instance
}

} // namespace xentara::plugins::templateUplink