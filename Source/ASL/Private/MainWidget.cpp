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

    TArray<FString> Parts;
    sDHString.ParseIntoArray(Parts, TEXT("-"), true);

    if (Parts.Num() == 2 && Parts[1].Len() >= 2)
    {
        sDong = Parts[0] + TEXT("동");  // 한글 직접 추가
        int32 iFloorNum = FCString::Atoi(*Parts[1].Left(1));
        int32 iHoeNum = FCString::Atoi(*Parts[1].Right(Parts[1].Len() - 1));

        if (iFloorNum >= 1 && iFloorNum <= 9)
        {
            sFloor = FString::Printf(TEXT("%d층"), iFloorNum);
            sHoe = FString::Printf(TEXT("%d호"), iHoeNum);
        }
        else
        {
            sFloor = FString::Printf(TEXT("%d층"), iFloorNum);
            sHoe = FString::Printf(TEXT("%d호"), iHoeNum % 100);
        }

        //  디버깅용 로그 추가 (한글이 올바르게 표시되는지 확인)
        UE_LOG(LogTemp, Warning, TEXT("Parsed Address: %s, %s, %s"), *sDong, *sFloor, *sHoe);
    }
}


/*void UMainWidget::DHOnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
    ET_StringNumSet->SetText(FText::FromString(sDHString));
    
    TArray<FString> Parts;
    sDHString.ParseIntoArray(Parts, TEXT("-"), true);

    if (Parts.Num() == 2 && Parts[1].Len() >= 2)
    {
        sDong = Parts[0] + TEXT("동");
        int32 iFloorNum = FCString::Atoi(*Parts[1].Left(1));
        int32 iHoeNum = FCString::Atoi(*Parts[1].Right(Parts[1].Len() - 1));

        if (iFloorNum >= 1 && iFloorNum <= 9)
        {
            sFloor = FString::Printf(TEXT("%d층"), iFloorNum);
            sHoe = FString::Printf(TEXT("%호"), iHoeNum);
        }
        else
        {
            sFloor = FString::Printf(TEXT("%d층"), iFloorNum);
            sHoe = FString::Printf(TEXT("%호"), iHoeNum %100);
        }

    }
}*/
