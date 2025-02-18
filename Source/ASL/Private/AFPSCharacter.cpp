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
	bIsBirdView = true;

	GetCharacterMovement()->bConstrainToPlane = false;
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
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

	//UE_LOG(LogTemp, Warning, TEXT("Call InputAction Play"));

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhancedInputComponent)
	{
		enhancedInputComponent->BindAction(ia_move, ETriggerEvent::Triggered, this, &AAFPSCharacter::Move);
		enhancedInputComponent->BindAction(ia_rotate, ETriggerEvent::Triggered, this, &AAFPSCharacter::Look);
		enhancedInputComponent->BindAction(ia_RBclick, ETriggerEvent::Started, this, &AAFPSCharacter::RB_Click);
		enhancedInputComponent->BindAction(ia_RBclick, ETriggerEvent::Completed, this, &AAFPSCharacter::RB_Click);
		enhancedInputComponent->BindAction(ia_LBclick, ETriggerEvent::Started, this, &AAFPSCharacter::LB_Click);
		enhancedInputComponent->BindAction(ia_LBclick, ETriggerEvent::Completed, this, &AAFPSCharacter::LB_Click);
		enhancedInputComponent->BindAction(ia_Zoom, ETriggerEvent::Triggered, this, &AAFPSCharacter::Zoom);
		UE_LOG(LogTemp, Warning, TEXT("InputSet"));
	}

}


void AAFPSCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (Controller)
	{
		if(bIsBirdView!=true)
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
		UE_LOG(LogTemp, Warning, TEXT("Look Function Called - X: %f, Y: %f"), LookAxisVector.X, LookAxisVector.Y);
	}
	if(bIsBirdView)
	{
		if (bLBclicked)
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
			FVector2D MouseMove = Value.Get<FVector2D>();
			//AddMovementInput(GetActorUpVector(), mouseWalkSpeed * MouseMove.Y);
			//AddMovementInput(GetActorRightVector(), mouseWalkSpeed * MouseMove.X);
			//UE_LOG(LogTemp, Warning, TEXT("MouseMove Function Called - X: %f, Y: %f"), MouseMove.X, MouseMove.Y);
			FVector NewLocation = GetActorLocation() +
				(GetActorUpVector() * MouseMove.Y * mouseWalkSpeed) +
				(GetActorRightVector() * MouseMove.X * mouseWalkSpeed);

			SetActorLocation(NewLocation, true);


		}
	}
	
}

void AAFPSCharacter::RB_Click(const FInputActionValue& Value)
{
	bRBclicked = Value.Get<bool>();
	UE_LOG(LogTemp, Warning, TEXT("RB_Click called - bRBclicked: %s"), bRBclicked ? TEXT("TRUE") : TEXT("FALSE"));
}

void AAFPSCharacter::LB_Click(const FInputActionValue& Value)
{

	bLBclicked = Value.Get<bool>();
	UE_LOG(LogTemp, Warning, TEXT("LB_Click called - bLBclicked: %s"), bLBclicked ? TEXT("TRUE") : TEXT("FALSE"));

}

void AAFPSCharacter::Zoom(const FInputActionValue& Value)
{
	FVector wheelMove = Value.Get<FVector>();
	FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * mouseWalkSpeed * wheelMove.X);

	SetActorLocation(NewLocation, true);

}