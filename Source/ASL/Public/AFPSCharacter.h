// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "inputactionvalue.h"
#include "AFPSCharacter.generated.h"

UCLASS()
class ASL_API AAFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputAction* ia_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputAction* ia_Rotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputAction* ia_LBClick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputAction* ia_RBClick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputAction* ia_Zoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputMappingContext* imc_FPSmapping;


	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void RB_Click(const FInputActionValue& Value);
	void LB_Click(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);

	bool bLBclicked;
	bool bRBclicked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBirdView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float walkSpeed = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mouseWalkSpeed = 10;

	UFUNCTION(BlueprintCallable)
	void SetBirdMode();

	UFUNCTION(BlueprintCallable)
	void SetFPSMode();



};