// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/EditableText.h"
#include "Input/Reply.h" 
#include "Widgets/Input/SEditableText.h"

void UMainWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ET_StringNumSet)
    {
        ET_StringNumSet->OnTextChanged.AddDynamic(this, &UMainWidget::DHOnTextChanged);
        ET_StringNumSet->OnTextCommitted.AddDynamic(this, &UMainWidget::DHOnTextCommitted);
    }

}

void UMainWidget::DHOnTextChanged(const FText& Text)
{

	FString sInputDH = Text.ToString();

    sDHString.Empty();

    // Erase not Number
    for (TCHAR Character : sInputDH)
    {
        if (FChar::IsDigit(Character) || Character == '-')
        {
            sDHString.AppendChar(Character);
        }
    }

    // If Edited Change string
    if (sInputDH != sDHString)
    {
        ET_StringNumSet->SetText(FText::FromString(sDHString));
    }

}

void UMainWidget::DHOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
    ET_StringNumSet->SetText(FText::FromString(sDHString));
    

}
