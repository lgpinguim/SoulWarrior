// Fill out your copyright notice in the Description page of Project Settings.


#include "Collider.h"

#include "ColliderMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACollider::ACollider()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	MeshComponent= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    if (MeshComponentAsset.Succeeded())
    {
	    MeshComponent->SetStaticMesh(MeshComponentAsset.Object);
    	MeshComponent->SetRelativeLocation(FVector(0.f,0.f,-40.f));
    	MeshComponent->SetWorldScale3D(FVector(0.8f));
    }

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-45.f,0.f,0.f));
	SpringArm->TargetArmLength=400.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed=3.0f;
	//
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm,USpringArmComponent::SocketName);
	
	CameraInput=FVector2D(0.f);
	

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	

}

// Called when the game starts or when spawned
void ACollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = GetActorRotation();

	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);

	FRotator NewSpringArmRotation = SpringArm->GetComponentRotation();
	NewSpringArmRotation.Pitch += CameraInput.Y;

	SpringArm->SetWorldRotation(NewSpringArmRotation);
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch += CameraInput.Y,-80.f,-15.f);

}

// Called to bind functionality to input
void ACollider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFoward"),this,&ACollider::MoveFoward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&ACollider::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("CameraPitch"),this,&ACollider::PitchCamera);
	PlayerInputComponent->BindAxis(TEXT("CameraYaw"),this,&ACollider::YawCamera);
	

}

void ACollider::MoveFoward(float Input)
{
	FVector Forward = GetActorForwardVector();
	AddMovementInput(Input* Forward);
	
}

void ACollider::MoveRight(float Input)
{
	FVector Right = GetActorRightVector();
	AddMovementInput(Input* Right);
}

void ACollider::PitchCamera(float AxisValue)
{
	CameraInput.Y= AxisValue;
	
}

void ACollider::YawCamera(float AxisValue)
{
	CameraInput.X= AxisValue;
}

