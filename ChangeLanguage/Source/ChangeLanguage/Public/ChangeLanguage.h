// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "Framework/Commands/Commands.h"
#include "Styling/AppStyle.h"
#include "Framework/Application/IInputProcessor.h"

#include "ChangeLanguage.generated.h"


DECLARE_DELEGATE(FActionKeySelectedDelegate);

UCLASS(config = EditorPerProjectUserSettings) // Give it a better looking name in UI
class UChangeLanguageDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere,BlueprintReadOnly, Category = "Change Language Settings")
	FString MainLanguage = "en";

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Change Language Settings")
	FString SupportLanguage = "ru";

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Change Language Settings")
	TArray<FKey> ChangeLanguageComboKeys = { EKeys::LeftShift, EKeys::Z };

	virtual FName GetCategoryName() const override;
	virtual FName GetSectionName() const override;

};

class FComboActionInputProcessor : public IInputProcessor
{
public:

	FComboActionInputProcessor() {};

	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;

	virtual bool HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;

	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;

	FActionKeySelectedDelegate ActionActiveDelegate;

	TArray<FKey> KeysToActivate;

	TArray<FKey> ActiveKeys;

private:
	bool CheckKey();
};

class FChangeLanguageModule : public IModuleInterface
{
public:

	TSharedPtr<FComboActionInputProcessor> ChangeLanguageProcessor;

	UChangeLanguageDeveloperSettings* ChangeLanguageDeveloperSettings;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};

#undef LOCTEXT_NAMESPACE
