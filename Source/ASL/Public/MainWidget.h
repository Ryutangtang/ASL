// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASL_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UEditableText* ET_StringNumSet;

	UFUNCTION()
	void DHOnTextChanged(const FText& Text);

	UFUNCTION()
	void DHOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString sDHString;

};
