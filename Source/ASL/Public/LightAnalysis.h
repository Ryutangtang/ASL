// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LightAnalysis.generated.h"

/**
 * 
 */
UCLASS()
class ASL_API ULightAnalysis : public UUserWidget
{
	GENERATED_BODY()
	

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UEditableText* ET_Hour; 
    
    UPROPERTY(meta = (BindWidget))
    class UEditableText* ET_Minute;
    
    UPROPERTY(meta = (BindWidget))
    class USlider* SL_TimeSlider;

    UFUNCTION()
    void HourOnTextChanged(const FText& Text);
    
    UFUNCTION()
    void HourOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

    UFUNCTION()
    void MinuteOnTextChanged(const FText& Text);

    UFUNCTION()
    void MinuteOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

    UFUNCTION()
    void OnTimeSliderChanged(float Value);

    FString sHour;
    FString sMinute;
    
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
    int iHour = 12;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int iMinute = 0;

};
