// Fill out your copyright notice in the Description page of Project Settings.


#include "LightAnalysis.h"
#include "Components/EditableText.h"
#include "Input/Reply.h" 
#include "Widgets/Input/SEditableText.h"
#include "Components/Slider.h"

void ULightAnalysis::NativeConstruct()
{
	Super::NativeConstruct();

    if (ET_Hour)
    {
        ET_Hour->OnTextChanged.AddDynamic(this, &ULightAnalysis::HourOnTextChanged);
        ET_Hour->OnTextCommitted.AddDynamic(this, &ULightAnalysis::HourOnTextCommitted);
    }
    
    if (ET_Minute)
    {
        ET_Minute->OnTextChanged.AddDynamic(this, &ULightAnalysis::MinuteOnTextChanged);
        ET_Minute->OnTextCommitted.AddDynamic(this, &ULightAnalysis::MinuteOnTextCommitted);
    }

    if (SL_TimeSlider)
    {
        SL_TimeSlider->OnValueChanged.AddDynamic(this, &ULightAnalysis::OnTimeSliderChanged);
        SL_TimeSlider->SetMinValue(5 * 60);  
        SL_TimeSlider->SetMaxValue(21 * 60);
    }
}

void ULightAnalysis::HourOnTextChanged(const FText& Text)
{

    FString InputHour = Text.ToString();

    sHour.Empty();

    // Erase not Number
    for (TCHAR Character : InputHour)
    {
        if (FChar::IsDigit(Character))
        {
            sHour.AppendChar(Character);
        }
    }

    if (sHour.Len() > 2)
    {
        sHour = sHour.Left(2);
    }

    // If Edited Change string
    if (InputHour != sHour)
    {
        ET_Hour->SetText(FText::FromString(sHour));
    }

}

void ULightAnalysis::HourOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{

    if (sHour.IsEmpty())
    {
        sHour = TEXT("12");
    }

    int32 Number = FCString::Atoi(*sHour);

    if (Number > 21)
    {
        sHour = TEXT("21");
    }

    if (Number < 4)
    {
        sHour = TEXT("04");
    }

    ET_Hour->SetText(FText::FromString(sHour));
    iHour = FCString::Atoi(*sHour);

    float SliderValue = (iHour * 60) + iMinute;
    SL_TimeSlider->SetValue(SliderValue);

}

void ULightAnalysis::MinuteOnTextChanged(const FText& Text)
{

    FString InputMinute = Text.ToString();

    sMinute.Empty();

    // Erase not Number
    for (TCHAR Character : InputMinute)
    {
        if (FChar::IsDigit(Character))
        {
            sMinute.AppendChar(Character);
        }
    }

    if (sMinute.Len() > 2)
    {
        sMinute = sMinute.Left(2);
    }

    // If Edited Change string
    if (InputMinute != sMinute)
    {
        ET_Minute->SetText(FText::FromString(sMinute));
    }

}

void ULightAnalysis::MinuteOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{

    if (sMinute.IsEmpty())
    {
        sMinute = TEXT("00");
    }

    int32 Number = FCString::Atoi(*sMinute);

    if (Number > 59)
    {
        sMinute = TEXT("59");
    }

    ET_Minute->SetText(FText::FromString(sMinute));
    iMinute = FCString::Atoi(*sMinute);

    float SliderValue = (iHour * 60) + iMinute;
    SL_TimeSlider->SetValue(SliderValue);

}

void ULightAnalysis::OnTimeSliderChanged(float Value)
{

    int32 TotalMinutes = FMath::RoundToInt(Value);
    iHour = TotalMinutes / 60;
    iMinute = TotalMinutes % 60;

    ET_Hour->SetText(FText::AsNumber(iHour));
    ET_Minute->SetText(FText::AsNumber(iMinute));

}
