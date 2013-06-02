#include "TileView.h"
#include "Logger.h"
#include "stringUtilities.h"

using namespace common;


TileView::TileView(){
	this->initialize();
}

TileView::TileView(TileModel* tModel){ //, Surface* fogSurface
	this->initialize();
	this->tileModel = tModel;
	//this->fog = fogSurface;
}

TileView::~TileView(){
	if (otherEntity)
		delete otherEntity;
	if (groundEntity)
		delete groundEntity;
	this->tileModel = NULL;
	//this->fog = NULL;
}

void TileView::initialize(){
	this->groundEntity = NULL;
	this->otherEntity = NULL;
	this->nextTile = NULL;
	this->relatedTile = NULL;
	this->isDrawable = true; //TODO: PASAR A FALSE
	this->isFogged = false;
	this->tileModel = NULL;
	//this->fog = NULL;
}

Entity * TileView::getGroundEntity(){
	return this->groundEntity;
}

Entity * TileView::getOtherEntity(){
	return this->otherEntity;
}

void TileView::setGroundEntity(Entity * e){
	this->groundEntity = e;
}

void TileView::setOtherEntity(Entity * e){
	this->otherEntity = e;
}

KeyPair TileView::getPosition(){
	return this->tileModel->getPosition();
}

void TileView::setNextTile(TileView* t){
	this->nextTile = t;
}

TileView* TileView::getNextTile(){
	return this->nextTile;
}

void TileView::setRelatedTile(TileView* t) {
	this->relatedTile = t;
}

TileView* TileView::getRelatedTile() {
	return this->relatedTile;
}

TileModel* TileView::getTileModel() {
	return this->tileModel;
}

bool TileView::drawable() {
	return this->tileModel->drawable();
}

bool TileView::EOL() {
	return this->tileModel->EOL();
}

string TileView::getGroundEntityName() {
	return this->tileModel->getGroundEntity()->name();
}

bool TileView::hasOtherEntity() {
	if (this->tileModel->getOtherEntity())
		return true;
	return false;
}

string TileView::getOtherEntityName() {
	//a este metodo usarlo con validaciones hasOtherEntity()
	return this->tileModel->getOtherEntity()->name();
}

void TileView::createGround(Sprite* sprite) {
	groundEntity = new Entity(this->tileModel->getPosition().first, this->tileModel->getPosition().second, sprite);
}

void TileView::createOtherEntity(Sprite* sprite) {
	otherEntity = new Entity(this->tileModel->getPosition().first, this->tileModel->getPosition().second, sprite);
}

void TileView::renderGround(Camera& camera) {
	this->getGroundEntity()->render(camera);
}

void TileView::setFogged(bool value) {
	this->isFogged = value;
	this->getGroundEntity()->setFogged(value);

	TileView* tileaux = this->getRelatedTile();
	if (tileaux) {
		while (tileaux != this){
			tileaux->getGroundEntity()->setFogged(value);
			if (tileaux->hasOtherEntity()) {
				tileaux->getOtherEntity()->setFogged(value);
			}
			tileaux = tileaux->getRelatedTile();
		}
	}
	else 
		if (this->hasOtherEntity()) {
			this->getOtherEntity()->setFogged(value);
		}
}

void TileView::renderEntity(Camera& camera){

	if (this->drawable()) {//TODO: PONER EN FALSE POR DEFAULT
		/*if (this->hasOtherEntity())
				this->getOtherEntity()->render(camera);*/

		TileView* tileaux = this->getRelatedTile();
		if (tileaux) {
			tileaux->getOtherEntity()->render(camera);
		}
		else 
			if (this->hasOtherEntity()) {
				this->getOtherEntity()->render(camera);
			}
	}

	//if (this->isFreezed){
	//	camera.render(this->getGroundEntity()->getSdlRect(),this->fog->getSdlSurface());
	//}
}

void TileView::update(){
	//this->getGroundEntity()->update();
	if (this->hasOtherEntity()){
		this->getOtherEntity()->update();
	}
}
