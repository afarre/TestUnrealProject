// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Tells unreal which character is currently selected
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	camera->SetRelativeLocation(FVector(0, 0, 40));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	isJumping = false;
	isSprinting = false;
	
	characterMovementComponent = GetCharacterMovement();
	characterMovementComponent->MaxWalkSpeed = 1000.0f;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Axis
	InputComponent->BindAxis("Horizontal", this, &AMyCharacter::HorizontalMove);
	InputComponent->BindAxis("Vertical", this, &AMyCharacter::VerticalMove);
	InputComponent->BindAxis("HorizontalRotation", this, &AMyCharacter::HorizontalRotation);
	InputComponent->BindAxis("VerticalRotation", this, &AMyCharacter::VerticalRotation);
	
	// Bind Actions
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::JumpAction);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::Sprint);
}

void AMyCharacter::JumpAction() {
	if (!isJumping) {
		isJumping = true;
		Jump();
		isJumping = false;
	}
}

void AMyCharacter::VerticalRotation(float value) {
	if (value) {
		float temp = camera->GetRelativeRotation().Pitch + value;

		if (temp < 65 && temp > -65) {
			camera->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}

void AMyCharacter::HorizontalRotation(float value) {
	if (value) {
		AddActorLocalRotation(FRotator(0, value, 0));
	}
}

void AMyCharacter::HorizontalMove(float value) {
	if (value) {
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AMyCharacter::VerticalMove(float value) {
	if (value) {
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void AMyCharacter::Sprint() {
	if (!isSprinting) {
		UE_LOG(LogTemp, Warning, TEXT("sprint ON"));
		characterMovementComponent->MaxWalkSpeed = 2000.0f;
	} else {
		UE_LOG(LogTemp, Warning, TEXT("sprint OFF"));
		characterMovementComponent->MaxWalkSpeed = 1000.0f;
	}
	isSprinting = !isSprinting;
}