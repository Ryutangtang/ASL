// Fill out your copyright notice in the Description page of Project Settings.


#include "AFPSCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


// Sets default values
AAFPSCharacter::AAFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	cameraComp->SetupAttachment(GetCapsuleComponent());
	cameraComp->bUsePawnControlRotation = true;

	bRBclicked = false;
	bLBclicked = false;

}

// Called when the game starts or when spawned
void AAFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pc = GetWorld()->GetFirstPlayerController();



	ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		subsys->AddMappingContext(imc_FPSmapping, 0);
	}
	pc->SetShowMouseCursor(true);

	SetBirdMode();
}

// Called every frame
void AAFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComponent)
	{
		enhancedInputComponent->BindAction(ia_Move, ETriggerEvent::Triggered, this, &AAFPSCharacter::Move);
		enhancedInputComponent->BindAction(ia_Rotate, ETriggerEvent::Triggered, this, &AAFPSCharacter::Look);
		enhancedInputComponent->BindAction(ia_RBClick, ETriggerEvent::Started, this, &AAFPSCharacter::RB_Click);
		enhancedInputComponent->BindAction(ia_RBClick, ETriggerEvent::Completed, this, &AAFPSCharacter::RB_Click);
		enhancedInputComponent->BindAction(ia_LBClick, ETriggerEvent::Started, this, &AAFPSCharacter::LB_Click);
		enhancedInputComponent->BindAction(ia_LBClick, ETriggerEvent::Completed, this, &AAFPSCharacter::LB_Click);
		enhancedInputComponent->BindAction(ia_Zoom, ETriggerEvent::Triggered, this, &AAFPSCharacter::Zoom);

	}

}


void AAFPSCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (Controller)
	{
		if(bIsBirdView==false)
		{

			AddMovementInput(GetActorForwardVector(), walkSpeed * MoveVector.Y);
			AddMovementInput(GetActorRightVector(), walkSpeed * MoveVector.X);

		}
	}
}

void AAFPSCharacter::Look(const FInputActionValue& Value)
{
	if (bRBclicked)
	{
		FVector2D LookAxisVector = Value.Get<FVector2D>();
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
		
	}
	if(bIsBirdView)
	{
		if (bLBclicked)
		{
			
			FVector2D MouseMove = Value.Get<FVector2D>();
			FVector NewLocation = GetActorLocation() +
				(cameraComp->GetUpVector() * -MouseMove.Y * mouseWalkSpeed) +
				(GetActorRightVector() * -MouseMove.X * mouseWalkSpeed);

			SetActorLocation(NewLocation, true);

		}
	}
	
}

void AAFPSCharacter::RB_Click(const FInputActionValue& Value)
{
	bRBclicked = Value.Get<bool>();
	
}

void AAFPSCharacter::LB_Click(const FInputActionValue& Value)
{

	bLBclicked = Value.Get<bool>();

}

void AAFPSCharacter::Zoom(const FInputActionValue& Value)
{
	
	if(bIsBirdView)
	{

		FVector wheelMove = Value.Get<FVector>();
		FVector NewLocation = GetActorLocation() + (cameraComp->GetForwardVector() * mouseWalkSpeed * wheelMove.X);

		SetActorLocation(NewLocation, true);

	}

}

void AAFPSCharacter::SetBirdMode()
{

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	bIsBirdView = true;
	GetCharacterMovement()->bConstrainToPlane = false;
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAFPSCharacter::SetFPSMode()
{

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	bIsBirdView = false;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = false;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
