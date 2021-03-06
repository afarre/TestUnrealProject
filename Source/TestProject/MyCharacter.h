// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacter.generated.h"

UCLASS()
class TESTPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void VerticalMove(float value);
	void HorizontalMove(float value);
	void HorizontalRotation(float value);
	void VerticalRotation(float value);
	void JumpAction();
	void Sprint();

	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent* camera;
	
	UPROPERTY(VisibleDefaultsOnly)
		UCharacterMovementComponent* characterMovementComponent;

	UPROPERTY()
		bool isJumping;

	UPROPERTY()
		bool isSprinting;
};
