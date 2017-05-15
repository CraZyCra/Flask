#include "shared.h"

Homebrew::Homebrew(std::shared_ptr<starlight::ui::Form> form, int i, string name, json properties)
{
	auto nameLabel = std::make_shared<Label>(starlight::VRect(48, i * 52, 320, 24));
	nameLabel->SetFont("roboto.24");
	nameLabel->SetText(name);

	auto descriptionLabel = std::make_shared<Label>(starlight::VRect(48, 24 + (i * 52), 320, 16));
	descriptionLabel->SetFont("roboto.16");
	descriptionLabel->SetText(properties["description"].get<std::string>());

	form->touchScreen->Add(descriptionLabel);
	form->touchScreen->Add(nameLabel);
}
