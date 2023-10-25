// Copyright Epic Games, Inc. All Rights Reserved.

#include "Workshop4Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AWorkshop4Character

AWorkshop4Character::AWorkshop4Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)


	Postions.Add(200);
	Postions.Add(400);
	Postions.Add(600);
	CurrentPos = 400;
}

void AWorkshop4Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	FVector Location = GetActorLocation();
	SetActorLocation(FVector(Location.X,CurrentPos,Location.Z));
}

void AWorkshop4Character::Ragdoll()
{
	GetMesh()->SetSimulatePhysics(true);
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWorkshop4Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWorkshop4Character::Move);

		EnhancedInputComponent->BindAction(RightAction, ETriggerEvent::Started, this, &AWorkshop4Character::MoveRight);
		EnhancedInputComponent->BindAction(LeftAction, ETriggerEvent::Started, this, &AWorkshop4Character::MoveLeft);


		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWorkshop4Character::Look);
		

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AWorkshop4Character::StartCrouch);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AWorkshop4Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	//FVector2D MovementVector = Value.Get<FVector2D>();

	//if (Controller != nullptr)
	//{
		// find out which way is forward
	//	const FRotator Rotation = Controller->GetControlRotation();
	//	const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
	//	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
	//	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		
	//	AddMovementInput(RightDirection, MovementVector.X);
	//}
}

void AWorkshop4Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWorkshop4Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	AddMovementInput(FVector(1.f,0.f,0.f), 1.f);

	if(Play)
	{
		RealScore += DeltaSeconds;
        
		ScoreRounded= round(RealScore);
	}
	

	
}

void AWorkshop4Character::MoveRight()
{
	
	
	if(CurrentPos+200<800)
	{
		FVector Location = GetActorLocation();
		SetActorLocation(FVector(Location.X,CurrentPos+250,Location.Z));
		CurrentPos += 250;
	}
	
}

void AWorkshop4Character::MoveLeft()
{
	
	if(CurrentPos-200>0)
	{
		FVector Location = GetActorLocation();
		SetActorLocation(FVector(Location.X,CurrentPos-250,Location.Z));
        CurrentPos -= 250;
	}
	
}

void AWorkshop4Character::StartCrouch()
{
	Crouch();
}
